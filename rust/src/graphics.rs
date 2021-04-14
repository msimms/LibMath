// by Michael J. Simms
// Copyright (c) 2020 Michael J. Simms

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#[derive(Copy, Clone)]
pub struct Point {
	pub x: f64,
	pub y: f64,
}

impl Point {
	pub fn new() -> Point {
		Point { x: 0.0, y: 0.0 }
	}
}

// Implements the ray casting/crossing number algorithm. Returns TRUE if the point is within the bounds of the points that specify the polygon (poly is a list of points)
pub fn is_point_in_polygon(test_point: Point, poly: &Vec<Point>) -> bool {

	// Sanity checks.
	let mut num_crossings = 0;
	let num_vertices = poly.len();

	// Need at least three points to make a polygon.
	if num_vertices < 3 {
		return false;
	}

	let test_x = test_point.x;
	let test_y = test_point.y;
	for i in 0..num_vertices {

		// Cache the y coordinate for the first point on the edge.
		let mut poly_pt = poly[i];
		let poly_pt1_y = poly_pt.y;

		// Cache the second point on the edge, handling the wrap around that happens when we close the polygon.
		let poly_pt2_x;
		let poly_pt2_y;
		if i == num_vertices - 1 {
			poly_pt = poly[0];
			poly_pt2_x = poly_pt.x;
			poly_pt2_y = poly_pt.y;
		}
		else {
			poly_pt = poly[i + 1];
			poly_pt2_x = poly_pt.x;
			poly_pt2_y = poly_pt.y;
		}

		// Test if the point is within the y limits of the edge.
		let crosses_y = ((poly_pt1_y <= test_y) && (poly_pt2_y > test_y)) || ((poly_pt1_y > test_y) && (poly_pt2_y <= test_y));
		if crosses_y {

			// Test if the ray extending to the right of the point crosses the edge.
			let poly_pt1_x = poly[i].x;
			if test_x <  poly_pt1_x + ((test_y - poly_pt1_y) / (poly_pt2_y - poly_pt1_y)) * (poly_pt2_x - poly_pt1_x) {
				num_crossings = num_crossings + 1;
			}
		}
	}

	(num_crossings & 1) != 0
}

// Implements the ray casting/crossing number algorithm. Returns TRUE if the point is within the bounds of the points that specify the polygon (poly is a list of points).
pub fn is_point_in_poly_array(test_x: f64, test_y: f64, poly: &Vec<Point>) -> bool {

	// Sanity checks.
	let mut num_crossings = 0;
	let num_vertices = poly.len();

	// Need at least three points to make a polygon
	if num_vertices < 3 {
		return false;
	}

	for i in 0..num_vertices {

		// Cache the y coordinate for the first point on the edge.
		let mut poly_pt = poly[i];
		let poly_pt1_y = poly_pt.y;

		// Cache the second point on the edge, handling the wrap around that happens when we close the polygon.
		let poly_pt2_x;
		let poly_pt2_y;
		if i == num_vertices - 1 {
			poly_pt = poly[0];
			poly_pt2_x = poly_pt.x;
			poly_pt2_y = poly_pt.y;
		}
		else {
			poly_pt = poly[i + 1];
			poly_pt2_x = poly_pt.x;
			poly_pt2_y = poly_pt.y;
		}

		// Test if the point is within the y limits of the edge.
		let crosses_y = ((poly_pt1_y <= test_y) && (poly_pt2_y > test_y)) || ((poly_pt1_y > test_y) && (poly_pt2_y <= test_y));
		if crosses_y {

			// Test if the ray extending to the right of the point crosses the edge.
			let poly_pt1_x = poly[i].x;
			if test_x <  poly_pt1_x + ((test_y - poly_pt1_y) / (poly_pt2_y - poly_pt1_y)) * (poly_pt2_x - poly_pt1_x) {
				num_crossings = num_crossings + 1;
			}
		}
	}

	(num_crossings & 1) != 0
}
