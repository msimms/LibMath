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

import argparse
import csv
import random
import distance
import graphics
import kmeans
import math
import os
import peaks
import signals
import statistics
import sys
from matplotlib import pyplot as plt
import numpy as np

def read_polygon_csv(csv_file_name):
    """Loads the polygon data test file."""
    points = []

    with open(csv_file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            new_point = {}
            new_point['x'] = float(row[0]) # longitude
            new_point['y'] = float(row[1]) # latitude
            new_point['z'] = float(row[2]) # altitude
            points.append(new_point)
	return points

def read_peak_data_csv(csv_file_name):
    """Loads the peak data test file."""
    columns = []
    ts_list = []
    x_list = []
    y_list = []
    z_list = []

    with open(csv_file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            ts_list.append(float(row[0])) # timestamp
            x_list.append(float(row[1]))  # x
            y_list.append(float(row[2]))  # y
            z_list.append(float(row[3]))  # z

	columns.append(ts_list)
	columns.append(x_list)
	columns.append(y_list)
	columns.append(z_list)
	return columns

def perform_distance_tests():
    """Performs unit tests on the distance module and prints the results."""
    print("Distance Tests:")
    print("---------------")

    #distance_calc = distance.hamming_distance("1011101", "1001001")
    #print("Hamming Distance: " + distance_calc)
    #assert(distance_calc == 2)
    #distance_calc = distance.levenshtein_distance("foo", "foobar")
    #print("Levenshtein Distance: " + distance_calc)
    #assert(distance_calc == 3)

    orlando_x = -81.38 # longitude
    orlando_y = 28.54 # latitude
    new_orleans_x = -90.08 # longitude
    new_orleans_y = 29.95 # latitude
    haversine_distance = distance.haversine_distance(orlando_y, orlando_x, 0.0, new_orleans_y, new_orleans_x, 0.0)
    print("Haversine Distance: " + str(haversine_distance))

def perform_statistics_tests():
    """Performs unit tests on the statistics module and prints the results."""
    print("Statistics Tests:")
    print("-----------------")

    v_flt = [ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 ]
    v_flt_avg = statistics.mean(v_flt)
    print("Average: " + str(v_flt_avg))
    variance = statistics.variance(v_flt, v_flt_avg)
    print("Variance: " + str(variance))
    print("Standard Deviation: " + str(statistics.stddev(v_flt, v_flt_avg)))

def perform_kmeans_tests():
    """Performs unit tests on the kmeans module and prints the results."""
    print("\nK-Means Tests:")
    print("--------------")

    kMeansIn = [0] * 10
    kMeansIn[0] = 7.123
    kMeansIn[1] = 0.999
    kMeansIn[2] = 0.001
    kMeansIn[3] = 0.5
    kMeansIn[4] = 0.75
    kMeansIn[5] = 0.002
    kMeansIn[6] = 3.0
    kMeansIn[7] = 2.0
    kMeansIn[8] = 5.0
    kMeansIn[9] = 0.001
    for k in range(2, 5):
        print("K = " + str(k))
        tags, avg_error = kmeans.kmeans_equally_space_centroids_1_d(kMeansIn, k, 0.001, 3)
        print("Tags: " + str(tags))
        print("Average Error: " + str(avg_error))

def perform_peak_finding_tests(csv_file_name, graph):
    """Performs unit tests on the peak finding module and prints the results."""
    print("\nPeak Finding Tests:")
    print("-------------------")

    real_path = os.path.realpath(csv_file_name)
    csv_data = read_peak_data_csv(real_path)
    csv_time_data = csv_data[0]
    csv_accel_data = csv_data[1:]
    x = np.arange(0,len(csv_time_data))
    axis_count = 0
    for axis_data in csv_accel_data:
        print("Axis " + str(axis_count) + ":")
        axis_count = axis_count + 1

        peak_count = 0
        peak_list = peaks.find_peaks_in_numeric_array(axis_data, 1.5)
        for peak in peak_list:
            print("Peak " + str(peak_count) + ": {" + str(peak.left_trough.x) + ", " + str(peak.peak.x) + ", " + str(peak.right_trough.x) + ", " + str(peak.area) + "}")
            peak_count = peak_count + 1

        if graph:
            y = np.array(axis_data)
            plt.plot(x,y)
            plt.xlabel("Time")
            plt.ylabel("Gs")
            plt.title('Accelerometer Data')
            plt.show()

def perform_graphics_tests(poly_file_name):
    """Performs unit tests on the graphics module and prints the results."""
    print("\nGraphics Tests:")
    print("---------------")

    orlando = {}
    orlando['x'] = -81.38 # longitude
    orlando['y'] = 28.54 # latitude
    orlando['z'] = 0.0
    
    new_orleans = {}
    new_orleans['x'] = -90.08 # longitude
    new_orleans['y'] = 29.95 # latitude
    new_orleans['z'] = 0.0

    real_path = os.path.realpath(poly_file_name)
    florida = read_polygon_csv(real_path)
    in_poly = graphics.is_point_in_polygon(orlando, florida)
    print("Is Orlando is in Florida: " + str(in_poly))
    in_poly = graphics.is_point_in_polygon(new_orleans, florida)
    print("Is New Orleans is in Florida: " + str(in_poly))

def perform_signal_tests():
    """Performs unit tests on the signals module and prints the results."""
    print("\nSignals Tests:")
    print("--------------")
    data = [1,2,3,4,5,6,7]
    print(data)
    print(signals.smooth(data, 1))
    print(signals.smooth(data, 2))
    print(signals.smooth(data, 3))

def main():
    # Parse command line options.
    parser = argparse.ArgumentParser()
    parser.add_argument("--peak_csv_file", default="../data/10_pullups.csv", help="CSV file containing test peak data", required=False)
    parser.add_argument("--poly_csv_file", default="../data/florida.csv", help="CSV file containing polygon data", required=False)
    parser.add_argument("--graph", action="store_true", default=False, help="Plots the test data and results, when applicable", required=False)

    try:
        args = parser.parse_args()
    except IOError as e:
        parser.error(e)
        sys.exit(1)

    perform_distance_tests()
    perform_statistics_tests()
    perform_kmeans_tests()

    if len(args.peak_csv_file) > 0:
        perform_peak_finding_tests(args.peak_csv_file, args.graph)
    if len(args.poly_csv_file) > 0:
        perform_graphics_tests(args.poly_csv_file)

    perform_signal_tests()

if __name__ == "__main__":
    main()
