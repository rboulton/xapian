/** @file geoencode.h
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

#ifndef GEOENCODE_INCLUDED_H
#define GEOENCODE_INCLUDED_H

#include <string>

namespace GeoEncode {

/** A latitude-longitude coordinate.
 */
struct LatLongCoord {
    /** The latitude, in degrees, range from -90 (south pole) to +90 (north
     *  pole).
     */
    double lat;

    /** The longitude in degrees, the usual range being from 0 <= longitude <
     *  360.
     *
     *  Note that longitudes will be wrapped when supplied to the encoding
     *  function, so other ranges may be used.
     */
    double lon;
};

/** Encode a coordinate and append it to a string.
 *
 * @param lat The latitude coordinate in degrees (ranging from -90 to +90)
 * @param lon The longitude coordinate in degrees (any range is valid -
 *            longitudes will be wrapped).  Note that decoding will return
 *            longitudes in the range 0 <= value < 360.
 * @param result The string to append the result to.
 *
 * @returns true if the encoding was successful, false if there was an error.
 * If there was an error, the result value will be unmodified.  The only cause
 * of error is out-of-range latitudes.  If there was no error, the string will
 * have been extended by 6 bytes.
 */
extern bool
encode(double lat, double lon, std::string & result);

/** Encode a coordinate and append it to a string.
 *
 * @param coord The coordinate to encode.
 * @param result The string to append the result to.
 *
 * @returns true if the encoding was successful, false if there was an error.
 * If there was an error, the result value will be unmodified.  The only cause
 * of error is out-of-range latitudes.  If there was no error, the string will
 * have been extended by 6 bytes.
 */
inline bool
encode(const LatLongCoord & coord, std::string & result)
{
    return GeoEncode::encode(coord.lat, coord.lon, result);
}

/** Decode a coordinate from a buffer.
 *
 * @param value A pointer to the start of the buffer to decode.
 *
 * @param len The length of the buffer in bytes.  The buffer must be at least 2
 *            bytes long (this constraint is not checked).
 *
 * @returns The decoded coordinate.
 *
 * No errors will be returned; any junk at the end of the value (ie, after the
 * first 6 bytes) will be ignored, and it is possible for invalid inputs to
 * result in out-of-range longitudes.
 */
extern LatLongCoord
decode(const char * value, size_t len);

/** Decode a coordinate from a string.
 *
 * @param value The string to decode.  This must be at least 2 bytes long (this
 *              constraint is not checked).
 *
 * @returns The decoded coordinate.
 *
 * No errors will be returned; any junk at the end of the value (ie, after the
 * first 6 bytes) will be ignored, and it is possible for invalid inputs to
 * result in out-of-range longitudes.
 */
inline LatLongCoord
decode(const std::string & value)
{
    return GeoEncode::decode(value.data(), value.size());
}

/** A class for decoding coordinates within a bounding box.
 *
 *  This class aborts decoding if it is easily able to determine that the
 *  encoded coordinate supplied is outside the bounding box, avoiding some
 *  unnecessary work.
 */
class DecoderWithBoundingBox {
    /** Longitude at western edge of bounding box.
     */
    double lon1;

    /** Longitude at eastern edge of bounding box.
     */
    double lon2;

    /** Minimum latitude in bounding box.
     */
    double min_lat;

    /** Maximum latitude in bounding box.
     */
    double max_lat;

    /** First byte of encoded form of coordinates with lon1.
     */
    unsigned char start1;

    /** First byte of encoded form of coordinates with lon2.
     */
    unsigned char start2;

    /** True if either of the poles are included in the range.
     */
    bool include_poles;

    /** Flag; true if the longitude range is discontinuous (ie, goes over the
     *  boundary at which longitudes wrap from 360 to 0).
     */
    bool discontinuous_longitude_range;

  public:
    /** Create a decoder with a bounding box.
     *
     *  The decoder will decode any encoded coordinates which lie inside the
     *  bounding box, and return false for any which lie outside the bounding
     *  box.
     *
     *  @param lat1 The latitude of the southern edge of the bounding box.
     *  @param lon1 The longitude of the western edge of the bounding box.
     *  @param lat2 The latitude of the northern edge of the bounding box.
     *  @param lon2 The longitude of the eastern edge of the bounding box.
     */
    DecoderWithBoundingBox(double lat1, double lon1, double lat2, double lon2);

    /** Decode a coordinate.
     *
     *  @param value The coordinate to decode.
     *
     *  @param result A structure to store the decoded coordinate in.
     *
     *  @returns true if the coordinate was in the bounding box (in which case,
     *           @a result will have been updated to contain the coordinate),
     *           or false if the coordinate is outside the bounding box.
     */
    bool decode(const std::string & value, LatLongCoord & result) const;
};

}

#endif /* GEOENCODE_INCLUDED_H */
