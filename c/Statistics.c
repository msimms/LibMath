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

#include <math.h>

#include "Statistics.h"

double statisticsAverageLong(const long* data, size_t numPoints)
{
	register long index;
	register long sum = 0;

	for (index = 0; index < numPoints; index++)
		sum = sum + data[index];
	return (double)sum / (double)numPoints;
}

double statisticsAverageDouble(const double* data, size_t numPoints)
{
	register long	index;
	register double	sum = 0;

	for (index = 0; index < numPoints; index++)
		sum = sum + data[index];
	return sum / (double)numPoints;
}

double statisticsVariance(const double* data, size_t numPoints, double mean)
{
	register long	index;
	register double	numerator = 0;
	
	for (index = 0; index < numPoints; index++)
		numerator = numerator + ((data[index] - mean) * (data[index] - mean));
	return numerator / (double)(numPoints - 1);
}

double statisticsStandardDeviation(const double* data, size_t numPoints, double mean)
{
	double var = statisticsVariance(data, numPoints, mean);
	return sqrt(var);
}

double statisticsMax(const double* data, size_t numPoints)
{
	register long	index;
	register double	result = data[0];
	
	for (index = 1; index < numPoints; index++)
	{
		if (data[index] > result)
			result = data[index];
	}
	return result;
}

size_t statisticsMaxInt(const size_t* data, size_t numPoints)
{
	register long	index;
	register size_t	result = data[0];
	
	for (index = 1; index < numPoints; index++)
	{
		if (data[index] > result)
			result = data[index];
	}
	return result;
}

double statisticsMin(const double* data, size_t numPoints)
{
	register long	index;
	register double	result = data[0];
	
	for (index = 1; index < numPoints; index++)
	{
		if (data[index] < result)
			result = data[index];
	}
	return result;
}

size_t statisticsMinInt(const size_t* data, size_t numPoints)
{
	register long	index;
	register size_t	result = data[0];
	
	for (index = 1; index < numPoints; index++)
	{
		if (data[index] < result)
			result = data[index];
	}
	return result;
}
