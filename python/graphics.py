#  MIT License
#
#  Copyright (c) 2019 Michael J Simms. All rights reserved.
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

def is_point_in_polygon(point, poly):
    """Implements the ray casting/crossing number algorithm. Returns TRUE if the point is within the bounds of the points that specify the polygon (poly is a list of points)."""

    # Sanity checks.
    if not isinstance(poly, list):
        return False

    num_crossings = 0
    num_vertices = len(poly)
    if num_vertices < 3: # Need at least three points to make a polygon
        return False

    test_x = point['x']
    test_y = point['y']
    for i in range(0, num_vertices):

        # Cache the y coordinate for the first point on the edge.
        poly_pt = poly[i]
        poly_pt1_y = poly_pt['y']

        # Cache the second point on the edge, handling the wrap around that happens when we close the polygon.
        if i == num_vertices - 1:
            poly_pt = poly[0]
            poly_pt2_x = poly_pt['x']
            poly_pt2_y = poly_pt['y']
        else:
            poly_pt = poly[i + 1]
            poly_pt2_x = poly_pt['x']
            poly_pt2_y = poly_pt['y']

        # Test if the point is within the y limits of the edge.
        crosses_y = ((poly_pt1_y <= test_y) and (poly_pt2_y > test_y)) or ((poly_pt1_y > test_y) and (poly_pt2_y <= test_y))
        if crosses_y:

            # Test if the ray extending to the right of the point crosses the edge.
            poly_pt1_x = (poly[i])['x']
            if test_x <  poly_pt1_x + ((test_y - poly_pt1_y) / (poly_pt2_y - poly_pt1_y)) * (poly_pt2_x - poly_pt1_x):
                num_crossings = num_crossings + 1

    return num_crossings & 1

def is_point_in_poly_array(test_x, test_y, poly):
    """Implements the ray casting/crossing number algorithm. Returns TRUE if the point is within the bounds of the points that specify the polygon (poly is a list of points)."""

    # Sanity checks.
    if not isinstance(poly, list):
        return False

    num_crossings = 0
    num_vertices = len(poly)
    if num_vertices < 3: # Need at least three points to make a polygon
        return False

    for i in range(0, num_vertices):

        # Cache the y coordinate for the first point on the edge.
        poly_pt = poly[i]
        if len(poly_pt) != 2:
            return False
        poly_pt1_y = poly_pt[1]

        # Cache the second point on the edge, handling the wrap around that happens when we close the polygon.
        if i == num_vertices - 1:
            poly_pt = poly[0]
            poly_pt2_x = poly_pt[0]
            poly_pt2_y = poly_pt[1]
        else:
            poly_pt = poly[i + 1]
            poly_pt2_x = poly_pt[0]
            poly_pt2_y = poly_pt[1]

        # Test if the point is within the y limits of the edge.
        crosses_y = ((poly_pt1_y <= test_y) and (poly_pt2_y > test_y)) or ((poly_pt1_y > test_y) and (poly_pt2_y <= test_y))
        if crosses_y:

            # Test if the ray extending to the right of the point crosses the edge.
            poly_pt1_x = (poly[i])[0]
            if test_x <  poly_pt1_x + ((test_y - poly_pt1_y) / (poly_pt2_y - poly_pt1_y)) * (poly_pt2_x - poly_pt1_x):
                num_crossings = num_crossings + 1

    return num_crossings & 1
