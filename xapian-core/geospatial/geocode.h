/** @file geocode.h
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

#ifndef XAPIAN_INCLUDED_COMPACTOR_H
#define XAPIAN_INCLUDED_COMPACTOR_H

namespace Xapian {

/** A latitude, longitude coordinate.
 */
struct LatLongCoord {
    /// The latitude coordinate, in degrees (range from -90 to +90).
    double lat;

    /** The longitude coordinate, in degrees.
     *
     *  The normal range for these is 0 <= lon < 360 degrees, but the encoding
     *  functions will handle values outside the range by wrapping them to the
     *  range.  Decoding functions will always produce values within this
     *  range.
     */
    double lon;
};

/** Encode a latitude, longitude pair.
 *
 *  @param lat The latitude to encode, in degrees.
 *  @param lon The longitude to encode, in degrees.
 *  @param result A buffer for the result, of size at least 6 bytes.
 */
bool geo_encode(double lat, double lon, char * result);

/** Encode a LatLongCoord.
 *
 *  @param lat The latitude to encode, in degrees.
 *  @param lon The longitude to encode, in degrees.
 *  @param result A buffer for the result, of size at least 6 bytes.
 *
 *  @returns false if the latitude coordinate was out of range, true otherwise.
 *  If this returns false, the result buffer will not have been modified; if
 *  this returns true, the first 6 bytes pointed to by the result parameter
 *  will have been set to the encoded value.
 */
inline bool geo_encode(const LatLongCoord & coord, char * result)
{
    return geo_encode(coord.lat, coord.lon, result);
}

/** Decode an encoded latitude, longitude pair.
 *
 *  @param value A pointer to the start of the encoded value.
 *  @param len The length of the encoded value.
 */
LatLongCoord geo_decode(const char * value, size_t len);

/** Decode an encoded latitude, longitude pair.
 */
inline LatLongCoord geo_decode(const string & value)
{
    return geo_decode(value.data(), value.size());
}


/** Check that coodinates are in a given range.
 */
class BoundingBoxChecker {
    string val1; // One end of the quick range check for the first 2 bytes.
    string val2; // Other end of the quick range check for the first 2 bytes.
    bool inside; // Whether values must be within the range, or outwith it.

  public:
    BoundingBoxChecker(double min_lat, double min_lon,
		       double max_lat, double max_lon);

    // Check if coordinate is within given bounding box.
    bool check(const string & value);

    // Check if coordinate is within given bounding box, and unpack it if so.
    bool check(const string & value, LatLongCoord & result);
};

}
