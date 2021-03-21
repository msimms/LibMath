//	MIT License
//
//  Copyright © 2021 Michael J Simms. All rights reserved.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

use statistics;

pub fn smooth(data_in: &Vec<f64>, window_size: usize) -> Vec<f64> {
    // Smooths the data, which should be a list, by averaging with the given window size.
    let data_in_len = data_in.len();
    let data_out_len = data_in_len - window_size + 1;
    if data_out_len <= 0 {
        return data_in.to_vec();
    }

    let mut data_out: Vec<f64> = Vec::new();
    for i in 0..data_out_len {
        let val = statistics::average_f64(&data_in[i..i + window_size].to_vec());
        data_out.push(val);
    }

    data_out
}
