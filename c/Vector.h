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

#ifndef _VECTOR_
#define _VECTOR_

typedef struct Vector
{
	double* data;
	size_t size;
} Vector;
typedef Vector* VectorPtr;

/**
 * Returns a vector of the specified size.
 */
VectorPtr vectorCreate(size_t size);

/**
 * Destroys a vector of the specified size.
 */
void vectorDestroy(VectorPtr vector);

/**
 * Returns a copy of vector B in vector A.
 */
void vectorCopy(const VectorPtr A, const VectorPtr B);

/**
 * Returns C = A x B, where A and B are vectors and C is a scalar.
 */
double vectorMultiply(const VectorPtr A, const VectorPtr B);

/**
 * Returns C = A - B, where A, B, and C are vectors.
 */
void vectorSubtract(const VectorPtr A, const VectorPtr B, VectorPtr C);

/**
 * Returns the dot product of A and B, where A and B are vectors.
 */
double vectorDot(const VectorPtr A, const VectorPtr B);

/**
 * Computes the length of the vector A.
 */
double vectorLength(const VectorPtr A);

/**
 * Normalizes vector A.
 */
void vectorNormalize(VectorPtr A);

/**
 * Returns C = A x B, where A, B, and C are 3x3 vectors.
 */
void vectorCross(const VectorPtr A, const VectorPtr B, VectorPtr C);

/**
 * Prints the contents of vector A to stdout.
 */
void vectorPrint(VectorPtr A);

#endif
