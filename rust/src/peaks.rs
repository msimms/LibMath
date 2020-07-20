// by Michael J. Simms
// Copyright (c) 2019 Michael J. Simms

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

#[derive(Copy, Clone)]
pub struct GraphPoint {
	x: usize,
	y: f64,
}

impl GraphPoint {
	pub fn new() -> GraphPoint {
		GraphPoint {x: 0, y: 0.0}
	}

	pub fn copy(&mut self, rhs: GraphPoint) {
		self.x = rhs.x;
		self.y = rhs.y;
	}

	pub fn equals(&mut self, rhs: GraphPoint) -> bool {
		self.x == rhs.x && self.y == rhs.y
	}

	pub fn clear(&mut self) {
		self.x = 0;
		self.y = 0.0;
	}
}

#[derive(Copy, Clone)]
pub struct GraphPeak {
	left_trough: GraphPoint,
	peak: GraphPoint,
	right_trough: GraphPoint,
	area: f64,
}

impl GraphPeak {
	pub fn new() -> GraphPeak {
		GraphPeak { left_trough: GraphPoint::new(), peak: GraphPoint::new(), right_trough: GraphPoint::new(), area: 0.0 }
	}

	pub fn copy(&mut self, rhs: GraphPeak) {
		self.left_trough = rhs.left_trough;
		self.peak = rhs.peak;
		self.right_trough = rhs.right_trough;
		self.area = rhs.area;
	}

	pub fn print(&self) {
		println!("L {}, P {}, R {}", self.left_trough.x, self.peak.x, self.right_trough.x);
	}

	pub fn equals(&mut self, rhs: GraphPeak) -> bool {
		self.left_trough.equals(rhs.left_trough) && self.peak.equals(rhs.peak) && self.right_trough.equals(rhs.right_trough)
	}

	pub fn less_than(&mut self, rhs: GraphPeak) -> bool {
		return self.area < rhs.area
	}
	pub fn greater_than(&mut self, rhs: GraphPeak) -> bool {
		return self.area > rhs.area
	}

	pub fn clear(&mut self) {
		self.left_trough.clear();
		self.peak.clear();
		self.right_trough.clear();
		self.area = 0.0;
	}
}

// Computes the area of the given peak.
pub fn compute_area(data: &Vec<f64>, current_peak: &mut GraphPeak) {
	current_peak.area = 0.0;
	
	if current_peak.left_trough.x < current_peak.right_trough.x {
		for index in current_peak.left_trough.x + 1..current_peak.right_trough.x + 1 {
			let b = data[index] + data[index - 1];
			current_peak.area += 0.5 * b;
		}
	}
}

// Returns a list of peaks in the given vector of numeric values. Only peaks that go above the given sigma line will be counted.
pub fn find_peaks(data: &Vec<f64>, sigmas: f64) -> Vec<GraphPeak> {
	let mut peaks: Vec<GraphPeak> = Vec::new();
	let mut current_peak = GraphPeak::new();

	let mean = statistics::average_f64(data);
	let stddev = sigmas * statistics::standard_deviation_f64(data, mean);
	let threshold = mean + stddev;

	for x in 0..data.len() {
		let y = data[x];

		if y < threshold {
			// Have we found a peak? If so, add it and start looking for the next one.
			if current_peak.right_trough.x > 0 {
				compute_area(data, &mut current_peak);
				peaks.push(current_peak);
				current_peak.clear();
			}

			// Are we looking for a left trough?
			else if current_peak.left_trough.x == 0 {
				current_peak.left_trough.x = x;
				current_peak.left_trough.y = y;
			}

			// If we have a left trough and an existing peak, assume this is the right trough - for now.
			else if current_peak.peak.x > current_peak.left_trough.x && current_peak.left_trough.x > 0 {
				current_peak.right_trough.x = x;
				current_peak.right_trough.y = y;
			}
			else {
				current_peak.left_trough.x = x;
				current_peak.left_trough.y = y;
			}
		}
		else if current_peak.left_trough.x > 0 { // Left trough is set.
			// Are we looking for a peak or is this bigger than the current peak?
			if current_peak.peak.x == 0 || y >= current_peak.peak.y {
				current_peak.peak.x = x;
				current_peak.peak.y = y;
			}
		}
		else if current_peak.right_trough.x > 0 { // Right trough is set.
			compute_area(data, &mut current_peak);
			peaks.push(current_peak);
			current_peak.clear();
		}
		else { // Nothing is set, but the value is above the threshold.
			current_peak.left_trough.x = x;
			current_peak.left_trough.y = y;
		}
	}

	peaks
}
