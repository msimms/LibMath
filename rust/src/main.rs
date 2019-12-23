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

mod distance;
mod kmeans;
mod peaks;
mod powers;
mod square_matrix;
mod statistics;
mod vector;

use std::env;
use std::error::Error;
use std::ffi::OsString;
use std::fs::File;

extern crate csv;

struct AccelerometerData {
    ts: Vec<f64>,
    x: Vec<f64>,
    y: Vec<f64>,
    z: Vec<f64>,
}

impl AccelerometerData {
    pub fn new() -> AccelerometerData {
        AccelerometerData { ts: Vec::new(), x: Vec::new(), y: Vec::new(), z: Vec::new() }
    }
}

fn read_accelerometer_csv(file_path: &str) -> AccelerometerData {
    let mut accel_vector = AccelerometerData::new();
    let mut file = match File::open(&file_path) {
        Err(why) => panic!("couldn't open {}: {}", file_path, why.description()),
        Ok(file) => file,
    };
    let mut reader = csv::Reader::from_reader(file);

    for record in reader.records() {
        for field in record.iter() {
            let ts: f64 = field[0].parse().unwrap();
            let x: f64 = field[1].parse().unwrap();
            let y: f64 = field[2].parse().unwrap();
            let z: f64 = field[3].parse().unwrap();
            accel_vector.ts.push(ts);
            accel_vector.x.push(x);
            accel_vector.y.push(y);
            accel_vector.z.push(z);
        }
    }
    accel_vector
}

fn help() {
	println!("Usage:");
	println!("\t--csv <csv file name for peak tests>");
}

fn vector_tests() {
	println!("Vector Tests:");
	println!("-------------");

	let mut v1 = vector::Vector::new(3);
	let mut v2 = vector::Vector::new(3);

	v1.set(0, 1.0);
	v1.set(1, 2.0);
	v1.set(2, 3.0);

	v2.set(0, 1.0);
	v2.set(1, 2.0);
	v2.set(2, 3.0);

    v1.print();
    v2.print();

    let v3 = v2.clone();
    let v_mult = v1.multiply(v2);
    println!("{}", v_mult);
    let v_dot = v1.dot(v3);
    println!("{}", v_dot);
}

fn square_matrix_tests() {
	println!("Square Matrix Tests:");
	println!("--------------------");

	let mut m = square_matrix::SquareMatrix::new(5);
	m.identity();
	println!("Identity matrix:");
	m.print();
	m.zero();
	println!("Zero matrix:");
	m.print();
	m.ones();
	println!("Ones matrix:");
	m.print();
	m.multiply_by_scalar(2.0);
	println!("Ones matrix multiplied by 2.0:");
	m.print();
	m.subtract_scalar(1.0);
	println!("2.0 matrix - 1.0:");
	m.print();
}

fn statistics_tests() {
	println!("\nStatistics Tests:");
	println!("-----------------");

	let v_int = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
	let v_int_avg = statistics::average_u32(&v_int);
	println!("Average: {}", v_int_avg);

	let v_flt = vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
	let v_flt_avg = statistics::average_f32(&v_flt);
	println!("Average: {}", v_flt_avg);
}

fn power_tests() {
	println!("\nPower Tests:");
	println!("------------");

	let nearest = powers::nearest_power_of_2(63);
	println!("Nearest power of 2 for {} is {}.", 63, nearest);
	assert!(nearest == 64);
}

fn distance_tests() {
	println!("\nDistance Tests:");
	println!("---------------");

	let mut distance = distance::hamming_distance("1011101", "1001001");
	println!("Hamming Distance: {}", distance);
	assert!(distance == 2);
	distance = distance::levenshtein_distance("foo", "foobar");
	println!("Levenshtein Distance: {}", distance);
	assert!(distance == 3);
}

fn kmeans_tests() {
	println!("\nK-Means Tests:");
	println!("--------------");

	let kmeans_in = vec![7.123, 0.999, 0.001, 0.5, 0.75, 0.002, 3.0, 2.0, 5.0, 0.001];
	let tags = kmeans::kmeans_equally_space_centroids_1_d(kmeans_in, 3, 0.001, 3);
	for tag in tags {
		println!("{}", tag);
	}
}

fn peak_finding_tests(accel_data: &AccelerometerData) {
    println!("\nPeak Finding Tests:");
    println!("-------------------");

    let x_peaks = peaks::find_peaks(&accel_data.x, 2.0);
    let y_peaks = peaks::find_peaks(&accel_data.y, 2.0);
    let z_peaks = peaks::find_peaks(&accel_data.z, 2.0);

    println!("\nX Peaks:");
    for peak in x_peaks {
        peak.print();
    }
    println!("\nY Peaks:");
    for peak in y_peaks {
        peak.print();
    }
    println!("\nZ Peaks:");
    for peak in z_peaks {
        peak.print();
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut csv_file_name = "";

    match args.len() {
        // no arguments passed
        1 => {
            help();
        },
        // one argument passed
        2 => {
            help();
        },
        // one command and one argument passed
        3 => {
            let cmd = &args[1];
            csv_file_name = &args[2];
        },
        // all the other cases
        _ => {
            help();
        }
    }

    vector_tests();
    println!("\n");
    square_matrix_tests();
    println!("\n");
    statistics_tests();
    println!("\n");
    power_tests();
    println!("\n");
    distance_tests();
    println!("\n");
    kmeans_tests();
    println!("\n");

	if csv_file_name.len() > 0 {
        let accel_data = read_accelerometer_csv(csv_file_name);
        peak_finding_tests(&accel_data);
    }
}
