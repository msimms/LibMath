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

#  Note class is only useful in python2 as python3 includes it's own statistics class

import math

def mean(data):
    """Computes the mean of the numbers in the array 'data'."""
    mean = 0.0
    for datum in data:
        mean = mean + datum
    return mean / len(data)

def variance(data, mean):
    """Computes the variance of the numbers in the array 'data'."""
    numerator = 0.0
    for datum in data:
        numerator = numerator + ((datum - mean) * (datum - mean))
    return numerator / (len(data) - 1)

def stddev(data, mean):
    """Computes the standard deviation of the numbers in the array 'data'."""
    var = variance(data, mean)
    return math.sqrt(var)
