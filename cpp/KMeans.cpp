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

#include "KMeans.h"
#include "Distance.h"
#include "Statistics.h"

#include <string.h>

namespace LibMath
{
	size_t* KMeans::kMeans1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters, double* centroids)
	{
		// Sanity check.
		if (k == 0)
		{
			return NULL;
		}

		// Create the output error array; describes the error for each data point.
		double* errors = (double*)new double[dataLen];
		if (!errors)
		{
			return NULL;
		}

		// Create the cluster means array; describes the error for each data point.
		size_t* clusterSizes = (size_t*)new size_t[k];
		if (!clusterSizes)
		{
			delete[] errors;
			return NULL;
		}

		// Create the output tag array.
		size_t* tags = (size_t*)new size_t[dataLen];
		if (!tags)
		{
			delete[] clusterSizes;
			delete[] errors;
			return NULL;
		}

		// Assignment step. Find the closest centroid for each data point.
		for (size_t dataIndex = 0; dataIndex < dataLen; ++dataIndex)
		{
			for (size_t clusterIndex = 0; clusterIndex < k; ++clusterIndex)
			{
				double distance = Distance::euclidianDistance1D(data[dataIndex], centroids[clusterIndex]);
				if ((clusterIndex == 0) || (distance < errors[dataIndex]))
				{
					tags[dataIndex] = clusterIndex;
					errors[dataIndex] = distance;
				}
			}
		}

		// Update step.
		double avgError = (double)0.0;
		size_t iterCount = 0;
		size_t numRelocations = 0;
		do {
			// Recompute cluster means.
			memset(centroids, 0, sizeof(double) * k);
			memset(clusterSizes, 0, sizeof(size_t) * k);
			for (size_t dataIndex = 0; dataIndex < dataLen; ++dataIndex)
			{
				size_t clusterIndex = tags[dataIndex];
				centroids[clusterIndex] += data[dataIndex];
				clusterSizes[clusterIndex]++;
			}
			for (size_t clusterIndex = 0; clusterIndex < k; ++clusterIndex)
			{
				centroids[clusterIndex] /= clusterSizes[clusterIndex];
			}

			// Measure each data point against it's own cluster mean, and all other cluster means.
			// Relocate the data point to the cluster that matches best.
			numRelocations = 0;
			for (size_t dataIndex = 0; dataIndex < dataLen; ++dataIndex)
			{
				for (size_t clusterIndex = 0; clusterIndex < k; ++clusterIndex)
				{
					double distance = Distance::euclidianDistance1D(data[dataIndex], centroids[clusterIndex]);
					if (distance < errors[dataIndex])
					{
						tags[dataIndex] = clusterIndex;
						errors[dataIndex] = distance;
						++numRelocations;
					}
				}
			}

			// Compute the average error.
			avgError = Statistics::averageDouble(errors, dataLen);

			++iterCount;
		} while ((avgError > maxError) && (iterCount < maxIters) && (numRelocations > 0));

		// Free memory.
		delete[] clusterSizes;
		delete[] errors;

		return tags;
	}

	size_t* KMeans::withEquallySpacedCentroids1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters)
	{
		// Sanity check.
		if (dataLen <= 1)
		{
			return NULL;
		}

		size_t* tags = NULL;

		double* centroids = (double*)new double[k];
		if (centroids)
		{
			// Select the k data points that are farthest apart from each other.
			double min = Statistics::min(data, dataLen);
			centroids[0] = min;
			double max = Statistics::max(data, dataLen);
			centroids[k - 1] = max;
			double increment = (max - min) / (double)(k - 1);
			for (size_t i = 1; i < k - 1; ++i)
			{
				centroids[i] = min + (increment * (double)i);
			}

			// Perform K Means clustering.
			tags = kMeans1D(data, dataLen, k, maxError, maxIters, centroids);

			// Clean up.
			delete[] centroids;
		}
		
		return tags;
	}

	size_t* KMeans::withRandCentroids1D(double* data, size_t dataLen, size_t k, double maxError, size_t maxIters)
	{
		// Sanity check.
		if (dataLen <= 1)
		{
			return NULL;
		}

		size_t* tags = NULL;

		double* centroids = (double*)new double[k];
		if (centroids)
		{
			// Randomly select starting centroids.
			for (size_t i = 0; i < k; ++i)
			{
				size_t selected = rand() % k;
				centroids[i] = data[selected];
			}

			// Perform K Means clustering.
			tags = kMeans1D(data, dataLen, k, maxError, maxIters, centroids);

			// Clean up.
			delete[] centroids;
		}
		
		return tags;
	}
}

