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

import random
import distance
import kmeans

def main():
    #print("Distance Tests:")
    #print("---------------")

    #distance_calc = distance.hamming_distance("1011101", "1001001")
    #print("Hamming Distance: " + distance_calc)
    #assert(distance_calc == 2)
    #distance_calc = distance.levenshtein_distance("foo", "foobar")
    #print("Levenshtein Distance: " + distance_calc)
    #assert(distance_calc == 3)

    print("K-Means Tests:")
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

if __name__ == "__main__":
    main()
