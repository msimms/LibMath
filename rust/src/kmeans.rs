//	MIT License
//
//  Copyright © 2018-2021 Michael J Simms. All rights reserved.
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

use distance;
use statistics;

pub fn kmeans_1_d(data: Vec<f64>, k: usize, max_error: f64, max_iters: usize, centroids: &mut Vec<f64>) -> Vec<usize> {
    // Sanity check.
    if k == 0 {
        let tags = vec![0, 0];
        return tags;
    }

    let num_samples = data.len();

    // Create the output error array; describes the error for each data point.
    let mut errors = vec![0.0 as f64; num_samples];

    // Create the cluster means array; describes the error for each data point.
    let mut cluster_sizes = vec![0; num_samples];

    // Create the output tag array.
    let mut tags = vec![0; num_samples];

    // Assignment step. Find the closest centroid for each data point.
    for sample_index in 0..num_samples {
        for cluster_index in 0..k {
            let distance = distance::euclidian_distance_1_d(data[sample_index], centroids[cluster_index]);

            if (cluster_index == 0) || (distance < errors[sample_index]) {
                tags[sample_index] = cluster_index;
                errors[sample_index] = distance;
            }
        }
    }

    // Update step.
    let mut avg_error;
    let mut iter_count = 0;
    let mut num_relocations;
    while {

        // Recompute cluster means.
        for i in 0..centroids.len() {
            centroids[i] = 0.0;
        }
        for i in 0..cluster_sizes.len() {
            cluster_sizes[i] = 0;
        }
        for sample_index in 0..num_samples {
            let cluster_index = tags[sample_index];
            centroids[cluster_index] = centroids[cluster_index] + data[sample_index];
            cluster_sizes[cluster_index] = cluster_sizes[cluster_index] + 1;
        }
        for cluster_index in 0..k {
            centroids[cluster_index] = centroids[cluster_index] / cluster_sizes[cluster_index] as f64;
        }

        // Measure each data point against it's own cluster mean, and all other cluster means.
        // Relocate the data point to the cluster that matches best.
        num_relocations = 0;
        for sample_index in 0..num_samples {
            for cluster_index in 0..k {
                let distance = distance::euclidian_distance_1_d(data[sample_index], centroids[cluster_index]);

                if distance < errors[sample_index] {
                    tags[sample_index] = cluster_index;
                    errors[sample_index] = distance;
                    num_relocations = num_relocations + 1;
                }
            }
        }

        // Compute the average error.
        avg_error = statistics::average_f64(&errors);

        iter_count = iter_count + 1;

        (avg_error > max_error) && (iter_count < max_iters) && (num_relocations > 0)
    } {};

    tags
}

pub fn kmeans(data: Vec<f64>, num_dimensions: usize, k: usize, max_error: f64, max_iters: usize, centroids: &mut Vec<f64>) -> Vec<usize> {
    // Sanity check.
    if k == 0 {
        let tags = vec![0, 0];
        return tags;
    }

    let num_samples = data.len() / num_dimensions;

    // Create the output error array; describes the error for each data point.
    let mut errors = vec![0.0 as f64; num_samples];

    // Create the cluster means array; describes the error for each data point.
    let mut cluster_sizes = vec![0; num_samples];

    // Create the output tag array.
    let mut tags = vec![0; num_samples];

    // Assignment step. Find the closest centroid for each data point.
    for sample_index in 0..num_samples {
        for cluster_index in 0..k {
            let slice_index_lower = sample_index * num_dimensions;
            let slice_index_upper = slice_index_lower + num_dimensions;
            let distance = distance::euclidian_distance_n_d(data[slice_index_lower..slice_index_upper].to_vec(), centroids.to_vec());

            if (cluster_index == 0) || (distance < errors[sample_index]) {
                tags[sample_index] = cluster_index;
                errors[sample_index] = distance;
            }
        }
    }

    // Update step.
    let mut avg_error;
    let mut iter_count = 0;
    let mut num_relocations;
    while {

        // Recompute cluster means.
        for i in 0..centroids.len() {
            centroids[i] = 0.0;
        }
        for i in 0..cluster_sizes.len() {
            cluster_sizes[i] = 0;
        }
        for data_index in 0..num_samples {
            let cluster_index = tags[data_index];
            centroids[cluster_index] = centroids[cluster_index] + data[data_index];
            cluster_sizes[cluster_index] = cluster_sizes[cluster_index] + 1;
        }
        for cluster_index in 0..k {
            centroids[cluster_index] = centroids[cluster_index] / cluster_sizes[cluster_index] as f64;
        }

        // Measure each data point against it's own cluster mean, and all other cluster means.
        // Relocate the data point to the cluster that matches best.
        num_relocations = 0;
        for data_index in 0..num_samples {
            for cluster_index in 0..k {
                let distance = distance::euclidian_distance_1_d(data[data_index], centroids[cluster_index]);

                if distance < errors[data_index] {
                    tags[data_index] = cluster_index;
                    errors[data_index] = distance;
                    num_relocations = num_relocations + 1;
                }
            }
        }

        // Compute the average error.
        avg_error = statistics::average_f64(&errors);

        iter_count = iter_count + 1;

        (avg_error > max_error) && (iter_count < max_iters) && (num_relocations > 0)
    } {};

    tags
}

pub fn kmeans_equally_space_centroids_1_d(data: Vec<f64>, k: usize, max_error: f64, max_iters: usize) -> Vec<usize> {
    // Sanity check.
    if data.len() <= 1 {
        let tags = vec![0, 0];
        return tags;
    }

    let mut centroids = vec![0.0; k];

    // Select the k data points that are farthest apart from each other.
    let min = statistics::min_f64(&data);
    let max = statistics::max_f64(&data);
    let increment = (max - min) / (k - 1) as f64;
    centroids[0] = min;
    centroids[k - 1] = max;
    for i in 0..k {
        centroids[i] = min + (increment * i as f64);
    }

    // Perform K Means clustering.
    let tags = kmeans_1_d(data, k, max_error, max_iters, &mut centroids);
    tags
}

pub fn kmeans_equally_space_centroids(data: Vec<f64>, num_dimensions: usize, k: usize, max_error: f64, max_iters: usize) -> Vec<usize> {
    // Sanity check.
    if data.len() <= 1 {
        let tags = vec![0, 0];
        return tags;
    }

    let mut centroids = vec![0.0; k];

    // Select the k data points that are farthest apart from each other.
    let min = statistics::min_f64(&data);
    let max = statistics::max_f64(&data);
    let increment = (max - min) / (k - 1) as f64;
    centroids[0] = min;
    centroids[k - 1] = max;
    for i in 0..k {
        centroids[i] = min + (increment * i as f64);
    }

    // Perform K Means clustering.
    let tags = kmeans(data, num_dimensions, k, max_error, max_iters, &mut centroids);
    tags
}
