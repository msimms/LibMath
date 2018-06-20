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

#pragma once

#ifndef _SQUAREMATRIX_
#define _SQUAREMATRIX_

#include "Vector.h"

typedef struct SquareMatrix
{
	double** data;
	size_t size;
} SquareMatrix;
typedef SquareMatrix* SquareMatrixPtr;

/**
 * Returns a square matrix of the specified size.
 */
SquareMatrixPtr squareMatrixCreate(size_t size);

/**
 * Frees the memory of the square matrix of the specified size.
 */
void squareMatrixDestroy(SquareMatrixPtr matrix);

/**
 * Prints the matrix to standard out. Intended for testing and debugging.
 */
void squareMatrixPrint(SquareMatrixPtr matrix);

/**
 * Returns C = A x B, where A, B, and C are matrices.
 */
void squareMatrixMultiply(const SquareMatrixPtr A, const SquareMatrixPtr B, SquareMatrixPtr C);

/**
 * Returns C = A x B, where A is a matrix and B and C are vectors.
 */
void squareMatrixMultiplyByVector(const SquareMatrixPtr A, const VectorPtr B, VectorPtr C);

/**
 * Multiplies the matrix by the supplied scalar.
 */
void squareMatrixMultiplyByScalar(SquareMatrixPtr A, double B);

/**
 * Returns C = A - B, where A, B, and C are matrices.
 */
void squareMatrixSubtract(const SquareMatrixPtr A, const SquareMatrixPtr B, SquareMatrixPtr C);

/**
 * Subtracts the scalar from the vector.
 */
void squareMatrixSubtractScalar(SquareMatrixPtr A, double B);

/**
 * Sets the value of A to the zero matrix.
 */
void squareMatrixZero(SquareMatrixPtr A);

/**
 * Sets the value of A to the identity matrix.
 */
void squareMatrixIdentity(SquareMatrixPtr A);

/**
 * Sets the value of A to the matrix of all ones.
 */
void squareMatrixOnes(SquareMatrixPtr A);

/**
 * Returns the dot product of A (the current matrix) and B.
 */
double squareMatrixDot(const SquareMatrixPtr A, const SquareMatrixPtr B);

#endif
