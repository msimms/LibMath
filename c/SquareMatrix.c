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

#include "SquareMatrix.h"

SquareMatrixPtr squareMatrixCreate(size_t size)
{
	register size_t i;

	SquareMatrixPtr matrix = (SquareMatrixPtr)malloc(sizeof(SquareMatrix));
	if (matrix)
	{
		matrix->data = (double**)malloc(sizeof(double*) * size);
		matrix->size = size;

		for (i = 0; i < size; ++i)
			matrix->data[i] = (double*)malloc(sizeof(double) * size);
	}
	return matrix;
}

void squareMatrixDestroy(SquareMatrixPtr matrix)
{
	register size_t i;

	if (matrix != NULL)
	{
		for (i = 0; i < matrix->size; ++i)
		{
			free((void*)matrix->data[i]);
			matrix->data[i] = NULL;
		}
		free((void*)matrix->data);
		free((void*)matrix);
	}
}

void squareMatrixPrint(SquareMatrixPtr matrix)
{
	register size_t i, j;

	if (matrix != NULL)
	{
		for (i = 0; i < matrix->size; ++i)
		{
			printf("[ ");
			for (j = 0; j < matrix->size; ++j)
			{
				printf("%lf ", matrix->data[i][j]);
			}
			printf("]\n");
		}
		printf("\n");
	}
}

void squareMatrixMultiply(const SquareMatrixPtr A, const SquareMatrixPtr B, SquareMatrixPtr C)
{
	register size_t i, j, k;
	
	// Compute C = A x B
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < B->size; ++j)
		{
			C->data[i][j] = 0.0;
			for (k = 0; k < C->size; ++k)
			{
				C->data[i][j] += A->data[i][k] * B->data[k][j];
			}
		}
	}
}

void squareMatrixMultiplyByVector(const SquareMatrixPtr A, const VectorPtr B, VectorPtr C)
{
	register size_t i, j;
	
	// Compute C = A x B
	for (i = 0; i < A->size; ++i)
	{
		C->data[i] = 0.0;
		for (j = 0; j < B->size; ++j)
		{
			C->data[i] += A->data[i][j] * B->data[j];
		}
	}
}

void squareMatrixMultiplyByScalar(SquareMatrixPtr A, double B)
{
	register size_t i, j;
	
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			A->data[i][j] = A->data[i][j] * B;
		}
	}
}

void squareMatrixSubtract(const SquareMatrixPtr A, const SquareMatrixPtr B, SquareMatrixPtr C)
{
	register size_t i, j;

	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			C->data[i][j] = A->data[i][j] - B->data[i][j];
		}
	}
}

void squareMatrixSubtractScalar(SquareMatrixPtr A, double B)
{
	register size_t i, j;

	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			A->data[i][j] = A->data[i][j] - B;
		}
	}
}

void squareMatrixZero(SquareMatrixPtr A)
{
	register size_t i, j;
	
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			A->data[i][j] = 0.0;
		}
	}
}

void squareMatrixIdentity(SquareMatrixPtr A)
{
	register size_t i, j;
	
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			if (i == j)
				A->data[i][j] = 1.0;
			else
				A->data[i][j] = 0.0;
		}
	}
}

void squareMatrixOnes(SquareMatrixPtr A)
{
	register size_t i, j;
	
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < A->size; ++j)
		{
			A->data[i][j] = 1.0;
		}
	}
}

double squareMatrixDot(const SquareMatrixPtr A, const SquareMatrixPtr B)
{
	register size_t i, j;
	double dot = 0.0;
	
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < B->size; ++j)
		{
			dot +=	*(A->data[i] + j * A->size) +
					*(B->data[i] + j * B->size);
		}
	}
	return dot;
}
