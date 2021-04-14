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
#[allow(dead_code)]

use statistics;

/// Returns the Haversine distance between two points on the Earth's surface.
pub fn haversine_distance(loc1_lat: f64, loc1_lon: f64, loc1_alt: f64, loc2_lat: f64, loc2_lon: f64, loc2_alt: f64) -> f64 {
    let mut r = 6372797.560856; // radius of the earth in meters
    r = r + loc2_alt - loc1_alt;

    let lat_arc = (loc1_lat - loc2_lat).to_radians();
    let lon_arc = (loc1_lon - loc2_lon).to_radians();

    let mut lat_h = (lat_arc * 0.5).sin();
    lat_h = lat_h * lat_h;

    let mut lon_h = (lon_arc * 0.5).sin();
    lon_h = lon_h * lon_h;

    let tmp = loc1_lat.to_radians().cos() * loc2_lat.to_radians().cos();
    let rad = 2.0 * (lat_h + tmp * lon_h).sqrt().asin();

    rad * r
}

/// Computes the Hamming distance of the two strings.
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

/// Computes the Levenshtein distance between the two strings.
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
        let temp_v = v0.clone();
        v0 = v1.clone();
        v1 = temp_v.clone();
    }

    // Save the final distance calculation, before freeing the vector.
    let distance = v0[n - 1];
    distance
}

/// Computes the Euclidian distance between the two values.
pub fn euclidian_distance_1_d(pt1: f64, pt2: f64) -> f64 {
    let distance = (pt1 - pt2).abs();
    distance
}

/// Computes the Euclidian distance between the two points.
pub fn euclidian_distance_2_d(pt1_x: f64, pt1_y: f64, pt2_x: f64, pt2_y: f64) -> f64 {
    let temp_x = pt2_x - pt1_x;
    let temp_y = pt2_y - pt1_y;
    let distance = ((temp_x * temp_x) + (temp_y * temp_y)).sqrt();
    distance
}

/// Computes the Euclidian distance between two multidimensional points.
/// Points must have the same dimensionality.
pub fn euclidian_distance_n_d(pt1: Vec<f64>, pt2: Vec<f64>) -> f64 {
    let num_dimensions = pt1.len();
    let mut sum = 0.0;
    for dimension in 0..num_dimensions {
        let temp = pt2[dimension] - pt1[dimension];
        sum = sum + (temp * temp);
    }
    let distance = sum.sqrt();
    distance
}
