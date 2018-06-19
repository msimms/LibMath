// by Michael J. Simms
// Copyright (c) 1998 Michael J. Simms

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#ifndef _STATISTICS_
#define _STATISTICS_

/**
 * Computes the average value in the given array.
 */
static double statisticsAverageLong(const long* data, unsigned long numPoints);

/**
 * Computes the average value in the given array.
 */
static double statisticsAverageDouble(const double* data, unsigned long numPoints);

/**
 * Computes the variance of the given array with the mean value supplied.
 */
static double statisticsVariance(const double* data, unsigned long numPoints, double mean);

/**
 * Computes the standard deviation of the given array with the mean value supplied.
 */
static double statisticsStandardDeviation(const double* data, unsigned long numPoints, double mean);

/**
 * Finds the largest value in the array.
 */
static double statisticsMax(const double* data, unsigned long numPoints);

/**
 * Finds the smallest value in the array.
 */
static double statisticsMin(const double* data, unsigned long numPoints);

#endif