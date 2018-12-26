// by Michael J. Simms
// Copyright (c) 1997-2018 Michael J. Simms

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vector.h"

VectorPtr vectorCreate(size_t size)
{
	VectorPtr vector = (VectorPtr)malloc(sizeof(Vector));
	if (vector)
	{
		vector->size = size;
		vector->data = (double*)malloc(sizeof(double) * size);
	}
	return vector;
}

void vectorDestroy(VectorPtr vector)
{
	if (vector != NULL)
	{
		free((void*)vector->data);
		free((void*)vector);
	}
}

void vectorCopy(const VectorPtr A, const VectorPtr B)
{
	memcpy((void *)A->data, (void *)B->data, sizeof(double) * B->size);
}

double vectorMultiply(const VectorPtr A, const VectorPtr B)
{
	register size_t i;
	double C = 0;

	for (i = 0; i < A->size; ++i)
		C += A->data[i] * B->data[i];
	return C;
}

void vectorSubtract(const VectorPtr A, const VectorPtr B, VectorPtr C)
{
	register size_t i;

	for (i = 0; i < A->size; ++i)
		C->data[i] = A->data[i] - B->data[i];
}

double vectorDot(const VectorPtr A, const VectorPtr B)
{
	register size_t i;
	double result = 0.0;

	for (i = 0; i < A->size; ++i)
		result += (A->data[i] * B->data[i]);
	return result;
}

double vectorLength(const VectorPtr A)
{
	register size_t i;
	double sum = 0.0;

	for (i = 0; i < A->size; ++i)
		sum += (A->data[i] * A->data[i]);
	return (sqrt(sum));
}

void vectorNormalize(VectorPtr A)
{
	register size_t i;
	double norm;

	norm = vectorLength(A);
	for (i = 0; i < A->size; ++i)
		A->data[i] = A->data[i] / norm;
}

void vectorCross(const VectorPtr A, const VectorPtr B, VectorPtr C)
{
	C->data[0] = (B->data[1] * A->data[2]) - (B->data[2] * A->data[1]);
	C->data[1] = (B->data[2] * A->data[0]) - (B->data[0] * A->data[2]);
	C->data[2] = (B->data[0] * A->data[1]) - (B->data[1] * A->data[0]);
}

void vectorPrint(VectorPtr A)
{
	register size_t i;

	printf("[");
	for (i = 0; i < A->size; ++i)
		printf("%s%lf", i > 0 ? " " : "", A->data[i]);
	printf("]\n");
}
