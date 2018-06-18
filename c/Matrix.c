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

#include "Matrix.h"

MatrixPtr matrixCreate(size_t size)
{
	register size_t i;

	MatrixPtr matrix = (MatrixPtr)malloc(sizeof(Matrix));
	if (matrix)
	{
		matrix->data = (double**)malloc(sizeof(double*) * size);
		matrix->size = size;

		for (i = 0; i < size; ++i)
			matrix->data[i] = (double*)malloc(sizeof(double) * size);
	}
	return matrix;
}

void matrixDestroy(MatrixPtr matrix)
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

void matrixPrint(MatrixPtr matrix)
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

void matrixMultiply(const MatrixPtr A, const MatrixPtr B, MatrixPtr C)
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

void matrixMultiplyByVector(const MatrixPtr A, const VectorPtr B, VectorPtr C)
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

void matrixSubtract(const MatrixPtr A, const MatrixPtr B, MatrixPtr C)
{
	register size_t i, j;
	
	// Compute C = A - B
	for (i = 0; i < A->size; ++i)
	{
		for (j = 0; j < B->size; ++j)
		{
			C->data[i][j] = A->data[i][j] - B->data[i][j];
		}
	}
}

void matrixZero(MatrixPtr A)
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

void matrixIdentity(MatrixPtr A)
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

void matrixOnes(MatrixPtr A)
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

double matrixDot(const MatrixPtr A, const MatrixPtr B)
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
