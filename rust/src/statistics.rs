//	MIT License
//
//  Copyright © 2018 Michael J Simms. All rights reserved.
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

pub fn average_long(data: Vec<u32>) -> f32 {
    let mut sum = 0;

    for item in &data {
        sum = sum + *item;
    }

    let avg = sum as f32 / data.len() as f32;
    avg
}

pub fn average_float(data: Vec<f32>) -> f32 {
    let mut sum = 0.0;

    for item in &data {
        sum = sum + *item;
    }

    let denominator = data.len();
    sum = sum / denominator as f32;
    sum
}

pub fn variance(data: Vec<f32>, mean: f32) -> f32 {
    let mut numerator = 0.0;

    for item in &data {
        numerator = numerator + ((*item - mean) * (*item - mean));
    }

    let denominator = (data.len() - 1) as f32;
    let variance = numerator / denominator;
    variance
}

pub fn standard_deviation(data: Vec<f32>, mean: f32) -> f32 {
    let var = variance(data, mean);
    let std_dev = var.sqrt();
    std_dev
}

pub fn max(data: Vec<f32>) -> f32 {
    let mut result = data[0];
    
    for item in &data {
        if *item > result {
            result = *item;
        }
    }
    result
}

pub fn min(data: Vec<f32>) -> f32 {
    let mut result = data[0];
    
    for item in &data {
        if *item < result {
            result = *item;
        }
    }
    result
}