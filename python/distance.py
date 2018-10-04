#  MIT License
#
#  Copyright (c) 2018 Michael J Simms. All rights reserved.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.

import math

def haversine_distance(loc1_lat, loc1_lon, loc1_alt, loc2_lat, loc2_lon, loc2_alt):
    """Returns the Haversine distance between two points on the Earth's surface."""
    R = 6372797.560856 # radius of the earth in meters
    R = R + loc2_alt - loc1_alt

    lat_arc = math.radians(loc1_lat - loc2_lat)
    lon_arc = math.radians(loc1_lon - loc2_lon)

    lat_h = math.sin(lat_arc * 0.5)
    lat_h = lat_h * lat_h

    lon_h = math.sin(lon_arc * 0.5)
    lon_h = lon_h * lon_h

    tmp = math.cos(math.radians(loc1_lat)) * math.cos(math.radians(loc2_lat))
    rad = 2.0 * math.asin(math.sqrt(lat_h + tmp * lon_h))

    return rad * R

def haversine_distance_ignore_altitude(loc1_lat, loc1_lon, loc2_lat, loc2_lon):
    """Returns the Haversine distance between two points on the Earth's surface."""
    R = 6372797.560856 # radius of the earth in meters

    lat_arc = math.radians(loc1_lat - loc2_lat)
    lon_arc = math.radians(loc1_lon - loc2_lon)

    lat_h = math.sin(lat_arc * 0.5)
    lat_h = lat_h * lat_h

    lon_h = math.sin(lon_arc * 0.5)
    lon_h = lon_h * lon_h

    tmp = math.cos(math.radians(loc1_lat)) * math.cos(math.radians(loc2_lat))
    rad = 2.0 * math.asin(math.sqrt(lat_h + tmp * lon_h))

    return rad * R

def euclidian_distance_1_d(pt1, pt2):
    return abs(pt1 - pt2)

def euclidian_distance_2_d(pt1_x, pt1_y, pt2_x, pt2_y):
    temp_x = pt2_x - pt1_x
    temp_y = pt2_y - pt1_y
    return math.sqrt((temp_x * temp_x) + (temp_y * temp_y))
