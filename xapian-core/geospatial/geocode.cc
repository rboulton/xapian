/** @file geocode.cc
 * @brief Encodings for geospatial coordinates.
 */
/* Copyright (C) 2011 Richard Boulton
 * Based closely on a python version, copyright (C) 2010 Olly Betts
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <config.h>

#include "geocode.h"

#include <cmath>
#include <string>

using namespace std;

/** Angles, split into degrees, minutes and seconds.
 *
 *  Only designed to work with positive angles.
 */
struct DegreesMinutesSeconds {
    int degrees;
    int minutes;
    int seconds;
    int sec16ths;

    // Initialise with a (positive) angle, as an integer representing the
    // number of 16ths of a second, rounding to nearest.  The range of valid
    // angles is assumed to be 0 <= angle in degres < 360, so range of
    // angle_16th_secs is 0..20735999, which fits easily into a 32 bit int.
    DegreesMinutesSeconds(int angle_16th_secs) {
	degrees = angle_16th_secs / (3600 * 16);
	angle_16th_secs = angle_16th_secs % (3600 * 16);
	minutes = angle_16th_secs / (60 * 16);
	angle_16th_secs = angle_16th_secs % (60 * 16);
	seconds = angle_16th_secs / 16;
	sec16ths = angle_16th_secs % 16;
    }
};

bool
geo_encode(double lat, double lon, char * result)
{
    // Check range of latitude.
    if (rare(lat < -90.0 || lat > 90.0)) {
	return false;
    }
    // Calc latitude and longitude in integral number of 16ths of a second
    int lat_int = round((lat + 90.0) * 57600.0);
    int lon_int;
    if (lat_int == 0 || lat_int == 57600 * 180) {
	lon_int = 0;
    } else {
	// Wrap longitude to range [0,360).
	lon = fmod(lon, 360.0);
	if (lon < 0) {
	    lon += 360;
	}
	lon_int = round(lon * 57600.0);
	if (lon_int == 57600 * 360) {
	    lon_int = 0;
	}
    }

    DegreesMinutesSeconds lat_dms(lat_int);
    DegreesMinutesSeconds lon_dms(lon_int);

    // Add degrees parts as first two bytes.  Make longitude the most
    // significant part, so that longitude ranges can be checked using byte
    // comparisons; longitude is more likely to be a good discriminator than
    // latitude, since it has a larger range, and most items of interest are
    // probably spread out east-west, rather than from pole to pole.
    unsigned dd = lat_dms.degrees + lon_dms.degrees * 181;
    // dd is in range 0..180+360*181 = 0..65340
    result[0] = char(dd >> 8);
    result[1] = char(dd & 0xff);

    // Add minutes next; 4 bits from each in the first byte.
    result[2] = char(((lat_dms.minutes / 4) << 4) | (lon_dms.minutes / 4));

    result[3] = char(
		     ((lat_dms.minutes % 4) << 6) |
		     ((lon_dms.minutes % 4) << 4) |
		     ((lat_dms.seconds / 15) << 2) |
		     (lon_dms.seconds / 15)
		    );

    result[4] = char(
		     ((lat_dms.seconds % 15) << 4) |
		     (lon_dms.seconds % 15)
		    );

    result[5] = char(
		     (lat_dms.sec16ths << 4) |
		     lon_dms.sec16ths
		    );

    return true;
}

struct LatLongCoord {
    double lat;
    double lon;
};

LatLongCoord
geo_decode(const char * value, size_t len)
{
    const unsigned char * ptr
	    = reinterpret_cast<const unsigned char *>(value);
    LatLongCoord result;
    unsigned tmp = (ptr[0] & 0xff) << 8 | (ptr[1] & 0xff);
    result.lat = tmp % 181;
    result.lon = tmp / 181;
    if (len > 2) {
	tmp = ptr[2];
	double lat_m = (tmp >> 4) * 4;
	double lon_m = (tmp & 0xf) * 4;

	if (len > 3) {
	    tmp = ptr[3];
	    lat_m += (tmp >> 6) & 3;
	    lon_m += (tmp >> 4) & 3;
	    double lat_s = ((tmp >> 2) & 3) * 15;
	    double lon_s = (tmp & 3) * 15;

	    if (len > 4) {
		tmp = ptr[4];
		lat_s += (tmp >> 4) & 0xf;
		lon_s += tmp & 0xf;

		if (len > 5) {
		    tmp = ptr[5];
		    lat_s += ((tmp >> 4) / 16.0);
		    lon_s += ((tmp & 0xf) / 16.0);
		}
	    }

	    lat_m += lat_s / 60.0;
	    lon_m += lon_s / 60.0;
	}

	result.lat += lat_m / 60.0;
	result.lon += lon_m / 60.0;
    }

    result.lat -= 90.0;
    return result;
}


// Test code

#include <stdio.h>
#include <stdlib.h>

bool
check(double lat, double lon, double expected_lat, double expected_lon)
{
    string encoded;
    char encoded_buf[6];
    bool ok = geo_encode(lat, lon, encoded_buf);
    encoded.append(encoded_buf, 6);
    if (!ok) {
	fprintf(stderr, "encoding failed\n");
	return false;
    }
    LatLongCoord result = geo_decode(encoded.data(), encoded.size());
    if (fabs(result.lat - expected_lat) > 0.00000001) {
	fprintf(stderr, "result.lat != expected_lat: %.15g != %.15g (input=%.15g,%.15g)\n", result.lat, expected_lat, lat, lon);
	return false;
    }
    if (fabs(result.lon - expected_lon) > 0.00000001) {
	fprintf(stderr, "result.lon != expected_lon: %.15g != %.15g (input=%.15g,%.15g)\n", result.lon, expected_lon, lat, lon);
	return false;
    }
    return true;
}

bool
check(double lat, double lon)
{
    return check(lat, lon, lat, lon);
}

bool
check_fail(double lat, double lon)
{
    char encoded[6];
    bool ok = geo_encode(lat, lon, encoded);
    if (ok) {
	fprintf(stderr, "expected failure but encoded without error\n");
	return false;
    }
    return true;
}

int main()
{
    // Check some roundtrips of things which encode precisely.
    // (encoding resolution is 16ths of a second).
    check(0, 0);
    check(0.2, 23.8);
    check((7)/(3600.0 * 16),
	  (7)/(3600.0 * 16));

    check(10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16),
	  10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16));
    check(-(10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16)),
	  -(10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16)),
	  -(10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16)),
	  360 -(10 + 7/60.0 + 5/3600.0 + 7/(3600.0 * 16))); 

    // This one is worth checking because it encodes the second byte as zero.
    check(10, 96);

    // Check the poles
    check(-90, 0);
    check(90, 0);
    check(-90, 1, -90, 0);
    check(90, 1, 90, 0);
    check(-89.9999999, 1, -90, 0);
    check(89.9999999, 1, 90, 0);
    check(0, 359.9999999, 0, 0);
    check(0, -359.9999999, 0, 0);

    check(-89.9999999, 359.9999999, -90, 0);
    check(-89.9999999, -359.9999999, -90, 0);
    check(89.9999999, 359.9999999, 90, 0);
    check(89.9999999, -359.9999999, 90, 0);

    // Check 
    check_fail(91, 0);
    check_fail(-91, 0);

    for (int i = 0; i != 1000000; ++i) {
	double lat = ((random() * 180.0) / RAND_MAX) - 90.0;
	double lon = ((random() * 360.0 * 10) / RAND_MAX) - (360.0 * 5);
	check(lat, lon,
	      round(lat * (3600.0 * 16)) / (3600.0 * 16),
	      round(fmod(lon + 3600.0, 360.0) * (3600.0 * 16)) / (3600.0 * 16)
	     );
    }
}
