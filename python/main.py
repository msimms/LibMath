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
import kmeans
import math
import peaks
import statistics
import sys

def read_csv(csv_file_name):
    columns = []
    ts_list = []
    x_list = []
    y_list = []
    z_list = []

    with open(csv_file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        for row in csv_reader:
            ts_list.append(float(row[0]))
            x_list.append(float(row[1]))
            y_list.append(float(row[2]))
            z_list.append(float(row[3]))

	columns.append(ts_list)
	columns.append(x_list)
	columns.append(y_list)
	columns.append(z_list)
	return columns

def main():
    # Parse command line options.
    parser = argparse.ArgumentParser()
    parser.add_argument("--csv_file_name", default="", help="CSV file containing test peak data", required=False)

    try:
        args = parser.parse_args()
    except IOError as e:
        parser.error(e)
        sys.exit(1)

    #print("Distance Tests:")
    #print("---------------")

    #distance_calc = distance.hamming_distance("1011101", "1001001")
    #print("Hamming Distance: " + distance_calc)
    #assert(distance_calc == 2)
    #distance_calc = distance.levenshtein_distance("foo", "foobar")
    #print("Levenshtein Distance: " + distance_calc)
    #assert(distance_calc == 3)

    print("Statistics Tests:")
    print("-----------------")

    v_flt = [ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 ]
    v_flt_avg = statistics.mean(v_flt)
    print("Average: " + str(v_flt_avg))
    variance = statistics.variance(v_flt, v_flt_avg)
    print("Variance: " + str(variance))
    print("Standard Deviation: " + str(statistics.stddev(v_flt, v_flt_avg)))

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
    tags = kmeans.kmeans_equally_space_centroids_1_d(kMeansIn, 3, 0.001, 3)
    print(tags)

    if len(args.csv_file_name) > 0:
        print("\nPeak Finding Tests:")
        print("-------------------")

        csv_data = read_csv(args.csv_file_name)
        csv_data = csv_data[1:]
        axis_count = 0
        for csv_column in csv_data:
            print("Axis " + str(axis_count) + ":")
            axis_count = axis_count + 1

            peak_count = 0
            peak_list = peaks.find_peaks_in_numeric_array(csv_column, 2.0)
            for peak in peak_list:
                print("Peak " + str(peak_count) + ": {" + str(peak.left_trough.x) + ", " + str(peak.peak.x) + ", " + str(peak.right_trough.x) + ", " + str(peak.area) + "}")
                peak_count = peak_count + 1

if __name__ == "__main__":
    main()
