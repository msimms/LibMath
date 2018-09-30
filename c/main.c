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

#include <stdio.h>
#include <assert.h>

#include "Distance.h"
#include "KMeans.h"
#include "Powers.h"
#include "SquareMatrix.h"
#include "Statistics.h"

int main(int argc, const char * argv[])
{
	printf("Square Matrix Tests:\n");
	printf("--------------------\n");

	SquareMatrixPtr m = squareMatrixCreate(5);
	squareMatrixIdentity(m);
	printf("Identity matrix:\n");
	squareMatrixPrint(m);
	squareMatrixDestroy(m);

	m = squareMatrixCreate(5);
	squareMatrixZero(m);
	printf("Zero matrix:\n");
	squareMatrixPrint(m);
	squareMatrixOnes(m);
	printf("Ones matrix:\n");
	squareMatrixPrint(m);
	squareMatrixMultiplyByScalar(m, 2.0);
	printf("Ones matrix multiplied by 2.0:\n");
	squareMatrixPrint(m);
	squareMatrixDestroy(m);

	printf("Statistics Tests:\n");
	printf("-----------------\n");

	long v_int[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double v_int_avg = statisticsAverageLong(v_int, 9);
	printf("Average: %lf\n", v_int_avg);
	assert(v_int_avg == 5.0);

	double v_flt[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	double v_flt_avg = statisticsAverageDouble(v_flt, 9);
	printf("Average: %lf\n", v_flt_avg);
	assert(v_flt_avg == 5.0);
	double variance = statisticsVariance(v_flt, 9, v_flt_avg);
	printf("Variance: %lf\n", variance);
	assert(variance == 7.5);
	printf("Standard Deviation: %lf\n", statisticsStandardDeviation(v_flt, 9, v_flt_avg));
	double max = statisticsMax(v_flt, 9);
	printf("Max: %lf\n", max);
	assert(max == 9.0);
	double min = statisticsMin(v_flt, 9);
	printf("Min: %lf\n\n", min);
	assert(min == 1.0);

	printf("Power Tests:\n");
	printf("------------\n");

	unsigned long nearest = NearestPowerOf2(63);
	printf("Nearest power of 2 for 63 is %ld.\n\n", nearest);
	assert(nearest == 64);

	printf("Distance Tests:\n");
	printf("---------------\n");

	size_t distance = hammingDistance("1011101", "1001001");
	printf("Hamming Distance: %zu\n", distance);
	assert(distance == 2);
	distance = levenshteinDistance("foo", "foobar");
	printf("Levenshtein Distance: %zu\n\n", distance);
	assert(distance == 3);

	printf("K-Means Tests:\n");
	printf("--------------\n");
	double kMeansIn[10];
	kMeansIn[0] = 7.123;
	kMeansIn[1] = 0.999;
	kMeansIn[2] = 0.001;
	kMeansIn[3] = 0.5;
	kMeansIn[4] = 0.75;
	kMeansIn[5] = 0.002;
	kMeansIn[6] = 3.0;
	kMeansIn[7] = 2.0;
	kMeansIn[8] = 5.0;
	kMeansIn[9] = 0.001;
	size_t* tags = kMeansEquallySpacedCentroids1D(kMeansIn, 10, 3, (double)0.001, 3);
	if (tags)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			printf("%zu\n", tags[i]);
		}
		free((void*)tags);
	}

	return 0;
}
 
