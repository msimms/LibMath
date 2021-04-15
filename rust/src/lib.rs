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

pub mod distance;
pub mod graphics;
pub mod kmeans;
pub mod peaks;
pub mod powers;
pub mod signals;
pub mod square_matrix;
pub mod statistics;
pub mod vector;

#[cfg(test)]
mod tests {
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
        let file = match File::open(&file_path) {
            Err(_why) => panic!("couldn't open {}", file_path),
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

    fn read_polygon_csv(file_path: &str) -> Vec<crate::graphics::Point> {
        let mut points = Vec::new(); 

        let file = match File::open(&file_path) {
            Err(_why) => panic!("couldn't open {}", file_path),
            Ok(file) => file,
        };
        let mut reader = csv::Reader::from_reader(file);

        for record in reader.records() {
            for field in record.iter() {
                let mut new_point = crate::graphics::Point::new();
                new_point.x = field[0].parse().unwrap();
                new_point.y = field[1].parse().unwrap();
                points.push(new_point);
            }
        }
        points
    }

    #[test]
    fn perform_vector_tests() {
        println!("Vector Tests:");
        println!("-------------");

        let mut v1 = crate::vector::Vector::new(3);
        let mut v2 = crate::vector::Vector::new(3);

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

    #[test]
    fn perform_square_matrix_tests() {
        println!("Square Matrix Tests:");
        println!("--------------------");

        let mut m = crate::square_matrix::SquareMatrix::new(5);
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

    #[test]
    fn perform_statistics_tests() {
        println!("\nStatistics Tests:");
        println!("-----------------");

        let v_int = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
        let v_int_avg = crate::statistics::average_u32(&v_int);
        println!("Average: {}", v_int_avg);

        let v_flt = vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0];
        let v_flt_avg = crate::statistics::average_f32(&v_flt);
        println!("Average: {}", v_flt_avg);
    }

    #[test]
    fn perform_power_tests() {
        println!("\nPower Tests:");
        println!("------------");

        let nearest = crate::powers::nearest_power_of_2(63);
        println!("Nearest power of 2 for {} is {}.", 63, nearest);
        assert!(nearest == 64);
    }

    #[test]
    fn perform_distance_tests() {
        println!("\nDistance Tests:");
        println!("---------------");

        // Hamming
        let mut distance = crate::distance::hamming_distance("1011101", "1001001");
        println!("Hamming Distance: {}", distance);
        assert!(distance == 2);

        // Levenshtein
        distance = crate::distance::levenshtein_distance("foo", "foobar");
        println!("Levenshtein Distance: {}", distance);
        assert!(distance == 3);

        // Haversine
        let orlando_x = -81.38; // longitude
        let orlando_y = 28.54; // latitude
        let new_orleans_x = -90.08; // longitude
        let new_orleans_y = 29.95; // latitude
        let haversine_distance = crate::distance::haversine_distance(orlando_y, orlando_x, 0.0, new_orleans_y, new_orleans_x, 0.0);
        println!("Haversine Distance: {}", haversine_distance);
        assert!((haversine_distance - 858538.6301523838).abs() < 0.0001);
    }

    #[test]
    fn perform_kmeans_tests() {
        println!("\nK-Means Tests:");
        println!("--------------");

        let k = 3;
        let max_error = 0.001;
        let max_iters = 3;

        let mut kmeans_in = vec![7.123, 0.999, 0.001, 0.5, 0.75, 0.002, 3.0, 2.0, 5.0, 0.001];
        let mut tags_and_error = crate::kmeans::kmeans_equally_space_centroids_1_d(kmeans_in, k, max_error, max_iters);
        println!("1D K-Means: {:?}", tags_and_error);

        let num_dimensions = 2;
        kmeans_in = vec![7.123, 1.0, 0.999, 1.0, 0.001, 1.0, 0.5, 1.0, 0.75, 1.0, 0.002, 1.0, 3.0, 1.0, 2.0, 1.0, 5.0, 1.0, 0.001, 1.0];
        tags_and_error = crate::kmeans::kmeans_equally_space_centroids(kmeans_in, num_dimensions, k, max_error, max_iters);
        println!("2D K-Means: {:?}", tags_and_error);
    }

    #[test]
    fn perform_peak_finding_tests() {
        println!("\nPeak Finding Tests:");
        println!("-------------------");

        let accel_csv_file_name = "../../data/10_pullups.cxv";
		let accel_data = read_accelerometer_csv(accel_csv_file_name);

        let x_peaks = crate::peaks::find_peaks(&accel_data.x, 1.5);
        let y_peaks = crate::peaks::find_peaks(&accel_data.y, 1.5);
        let z_peaks = crate::peaks::find_peaks(&accel_data.z, 1.5);

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

    #[test]
    fn perform_graphics_tests() {
        // Performs unit tests on the graphics module and prints the results.
        println!("\nGraphics Tests:");
        println!("----------------");

        let poly_csv_file_name = "../data/florida.cxv";
		let poly_data = read_polygon_csv(poly_csv_file_name);

        let mut orlando = crate::graphics::Point::new();
        orlando.x = -81.38; // longitude
        orlando.y = 28.54; // latitude
        
        let mut new_orleans = crate::graphics::Point::new();
        new_orleans.x = -90.08; // longitude
        new_orleans.y = 29.95; // latitude

        let mut in_poly = crate::graphics::is_point_in_polygon(orlando, &poly_data);
        println!("Is Orlando is in Florida: {}", in_poly);
        assert!(in_poly == true);

        in_poly = crate::graphics::is_point_in_polygon(new_orleans, &poly_data);
        println!("Is New Orleans is in Florida: {}", in_poly);
        assert!(in_poly == false);
    }

    #[test]
    fn perform_signal_tests() {
        // Performs unit tests on the signals module and prints the results."""
        println!("\nSignals Tests:");
        println!("--------------");

        let data = vec![1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0];
        println!("{:?}", data);
        println!("{:?}", crate::signals::smooth(&data, 1));
        println!("{:?}", crate::signals::smooth(&data, 2));
        println!("{:?}", crate::signals::smooth(&data, 3));
    }
}
