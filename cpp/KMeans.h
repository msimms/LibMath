// by Michael J. Simms
// Copyright (c) 2018 Michael J. Simms

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

#ifndef _KMEANS_
#define _KMEANS_

#include <stdlib.h>

namespace LibMath
{
	class KMeans
	{	
	public:
		/**
		 * Performs K Means clustering on a one dimensional array, using the provided centroids.
		 * Returns an array of length 'dataLen', that associates each input with a given cluster. 
		 */
		static size_t* kMeans1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters, double* clusters);

		/**
		 * Performs K Means clustering on a one dimensional array, setting the initial centroids to the data points farthest apart.
		 * Returns an array of length 'dataLen', that associates each input with a given cluster. 
		 */
		static size_t* withEquallySpacedCentroids1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters);

		/**
		 * Performs K Means clustering on a one dimensional array, using random initial centroids.
		 * Returns an array of length 'dataLen', that associates each input with a given cluster. 
		 */
		static size_t* withRandCentroids1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters);
	};
}

#endif
