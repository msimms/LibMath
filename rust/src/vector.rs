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
#[allow(dead_code)]

pub type VectorData = Vec<f64>;

#[derive(Clone)]
pub struct Vector {
    data: VectorData,
    size: usize,
}

impl Vector {
    pub fn new(size: usize) -> Vector {
        Vector { size: size, data: Vector::create_vector(size) }
    }

    fn create_vector(size: usize) -> VectorData {
        let v: VectorData = vec![0.0; size];
        v
    }

    pub fn print(&mut self) {
        print!("[");
        for i in 0..self.size {
            print!("{} ", self.data[i]);
        }
        println!("]");
    }

    pub fn set(&mut self, index: usize, val: f64) {
        self.data[index] = val;
    }

    pub fn multiply(&mut self, b: Vector) -> f64 {
        let mut c = 0.0;

        for i in 0..self.size {
            c = c + self.data[i] * b.data[i];
        }
        c
    }

    pub fn subtract(&mut self, b: Vector, c: &mut Vector) {
        for i in 0..self.size {
            c.data[i] = self.data[i] - b.data[i];
        }
    }

    pub fn dot(&mut self, b: Vector) -> f64 {
        let mut result = 0.0;

        // Compute the dot product
        for i in 0..self.size {
            result = result + (self.data[i] * b.data[i]);
        }
        result
    }

    pub fn length(&mut self) -> f64 {
        let mut sum = 0.0;

        for i in 0..self.size {
            sum = sum + (self.data[i] * self.data[i]);
        }
        let length = sum.sqrt();
        length
    }

    pub fn normalize(&mut self) {
        let norm = self.data.len() as f64;
        
        for i in 0..self.size {
            self.data[i] = self.data[i] / norm;
        }
    }

    pub fn cross(&mut self, a: Vector, b: Vector) {
        self.data[0] = (b.data[1] * a.data[2]) - (b.data[2] * a.data[1]);
        self.data[1] = (b.data[2] * a.data[0]) - (b.data[0] * a.data[2]);
        self.data[2] = (b.data[0] * a.data[1]) - (b.data[1] * a.data[0]);
    }
}
