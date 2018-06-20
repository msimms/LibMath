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

pub type MatrixData = Vec<Vec<f64>>;

pub struct SquareMatrix {
    data: MatrixData,
    size: usize,
}

impl SquareMatrix {
    pub fn new(size: usize) -> SquareMatrix {
        SquareMatrix { size: size, data: SquareMatrix::create_matrix(size) }
    }

    fn create_matrix(size: usize) -> MatrixData {
        let c: MatrixData = vec![vec![0.0; size]; size];
        c
    }

    pub fn print(&mut self) {
        for row in &mut self.data {
            print!("[");
            for i in 0..self.size {
    		    print!("{} ", row[i]);
            }
            println!("]");
        }
    }

    pub fn multiply(&mut self, b: f64) {
        for row in &mut self.data {
            for i in 0..self.size {
                row[i] = row[i] * b;
            }
        }
    }

    pub fn ones(&mut self) {
        for row in &mut self.data {
            for i in 0..self.size {
                row[i] = 1.0;
            }
        }
    }

    pub fn identity(&mut self) {
        let mut j = 0;
        for row in &mut self.data {
            for i in 0..self.size {
                if i == j {
                    row[i] = 1.0;
                }
                else {
                    row[i] = 0.0;
                }
            }
            j = j + 1;
        }
    }
}