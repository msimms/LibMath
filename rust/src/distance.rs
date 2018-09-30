// by Michael J. Simms
// Copyright (c) 2018 Michael J. Simms

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

use statistics;

pub fn hamming_distance(str1: &str, str2: &str) -> usize {
	let len1 = str1.len();

	// The strings must be the same length.
	if len1 != str2.len() {
		return usize::max_value();
    }

	let mut distance = 0;

    let str1_bytes = str1.as_bytes();
    let str2_bytes = str2.as_bytes();
	
    for i in 0..len1 {
		if str1_bytes[i] != str2_bytes[i] {
			distance = distance + 1;
        }
	}

	distance
}

pub fn levenshtein_distance(str1: &str, str2: &str) -> usize {
	let m = str1.len();
	let n = str2.len();

	// Test for empty strings.
	if m == 0 {
		return n;
    }
	if n == 0 {
		return m;
    }

    let mut v0 = vec![0; n];
    let mut v1 = vec![0; n];

    let str1_bytes = str1.as_bytes();
    let str2_bytes = str2.as_bytes();

    for i in 0..n {
		v0[i] = i;
	}
    for i in 0..m-1 {
		v1[0] = i + 1;
		
        for j in 0..n-1 {
			let mut costs = vec![0; 3]; // deletion, insertion, and substitution costs (in that order)
			costs[0] = v0[j + 1] + 1;
			costs[1] = v1[j] + 1;
			if str1_bytes[i] == str2_bytes[j] {
				costs[2] = v0[j];
            }
			else {
				costs[2] = v0[j] + 1;
            }
			v1[j + 1] = statistics::min_usize(&costs);
		}

		// Copy v1 to v0.
        let mut temp_v = v0.clone();
        v0 = v1.clone();
        v1 = temp_v.clone();
	}

	// Save the final distance calculation, before freeing the vector.
	let distance = v0[n - 1];
	distance
}

pub fn euclidian_distance_1_d(pt1: f32, pt2: f32) -> f32 {
	let distance = (pt1 - pt2).abs();
    distance
}

pub fn euclidian_distance_2_d(pt1_x: f32, pt1_y: f32, pt2_x: f32, pt2_y: f32) -> f32 {
	let temp_x = pt2_x - pt1_x;
	let temp_y = pt2_y - pt1_y;
	let distance = ((temp_x * temp_x) + (temp_y * temp_y)).sqrt();
    distance
}
