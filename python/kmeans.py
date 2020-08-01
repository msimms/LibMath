#  MIT License
#
#  Copyright (c) 2018 Michael J Simms. All rights reserved.
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.

import distance
import random

def kmeans_1_d(data, k, max_error, max_iters, centroids):
    """Performs  K-Means analysis using the specified centroids as starting points."""

    # Sanity check.
    data_len = len(data)
    if data_len <= 1:
        return [], None
    if k > data_len:
        return [], None

    # Create the output error array; describes the error for each data point.
    errors = [0.0] * data_len

    # Create the cluster means array; describes the error for each data point.
    cluster_sizes = [0] * data_len

    # Create the output tag array.
    tags = [0] * data_len

    # Assignment step. Find the closest centroid for each data point.
    for data_index in range(0, data_len):
        for cluster_index in range(0, k):
            distance_to_centroid = distance.euclidian_distance_1_d(data[data_index], centroids[cluster_index])
            if (cluster_index == 0) or (distance_to_centroid < errors[data_index]):
                tags[data_index] = cluster_index
                errors[data_index] = distance_to_centroid

    # Update step.
    avg_error = 0.0
    iter_count = 0
    num_relocations = 0
    while True:

        # Recompute cluster means.
        for i in range(0, len(centroids)):
            centroids[i] = 0.0
        for i in range(0, len(cluster_sizes)):
            cluster_sizes[i] = 0
        for data_index in range(0, data_len):
            cluster_index = tags[data_index]
            centroids[cluster_index] = centroids[cluster_index] + data[data_index]
            cluster_sizes[cluster_index] = cluster_sizes[cluster_index] + 1
        for cluster_index in range(0, k):
            if abs(cluster_sizes[cluster_index]) < 0.001: # Check for possible floating point zero value
                centroids[cluster_index] = 0.0
            else:
                centroids[cluster_index] = centroids[cluster_index] / cluster_sizes[cluster_index]

        # Measure each data point against it's own cluster mean, and all other cluster means.
        # Relocate the data point to the cluster that matches best.
        num_relocations = 0
        for data_index in range(0, data_len):
            for cluster_index in range(0, k):
                distance_to_centroid = distance.euclidian_distance_1_d(data[data_index], centroids[cluster_index])
                if distance_to_centroid < errors[data_index]:
                    tags[data_index] = cluster_index
                    errors[data_index] = distance_to_centroid
                    num_relocations = num_relocations + 1

        # Compute the average error.
        avg_error = sum(errors) / len(errors)

        iter_count = iter_count + 1

        if (avg_error <= max_error) or (iter_count >= max_iters) or (num_relocations <= 0):
            break

    return tags, avg_error

def kmeans_equally_space_centroids_1_d(data, k, max_error, max_iters):
    """Performs K-Means analysis on a one dimensional array, starting with centroids that are equally distributed across the rnage of input set."""

    # Sanity check.
    data_len = len(data)
    if data_len <= 1:
        return [], None
    if k > data_len:
        return [], None

    centroids = [0.0] * k

    # Select the k data points that are farthest apart from each other.
    data_min = min(data)
    centroids[0] = data_min
    data_max = max(data)
    centroids[k - 1] = data_max
    increment = (data_max - data_min) / (k - 1)
    for i in range(0, k):
        centroids[i] = data_min + (increment * i)

    # Perform K Means clustering.
    return kmeans_1_d(data, k, max_error, max_iters, centroids)

def kmeans_rand_centroids_1_d(data, k, max_error, max_iters):
    """Performs K-Means analysis on a one dimensional array, starting with centroids that are randomly distributed across the range of the input set."""

    # Sanity check.
    data_len = len(data)
    if data_len <= 1:
        return []
    if k > data_len:
        return []

    centroids = [0.0] * k

    # Randomly select starting centroids.
    for i in range(0, k):
        selected = random.randint(0, k)
        centroids[i] = data[selected]

    # Perform K Means clustering.
    return kmeans_1_d(data, k, max_error, max_iters, centroids)
