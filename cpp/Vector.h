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

#include <stdlib.h>

namespace LibMath
{
	class Vector
	{
	public:
		Vector(size_t size);
		virtual ~Vector(void);

		/**
		 * Returns the number of elements in the vector.
		 */		
		size_t size(void) const { return m_size; }

		/**
		 * Returns a copy of vector B in vector A.
		 */
		void copy(const Vector* B);

		/**
		 * Returns C = A x B, where A and B are vectors and C is a scalar.
		 */
		double multiply(const Vector* B);

		/**
		 * Returns C = A - B, where A, B, and C are vectors.
		 */
		void subtract(const Vector* B, Vector* C);

		/**
		 * Returns the dot product of A and B, where A and B are vectors.
		 */
		double dot(const Vector* B);

		/**
		 * Computes the length of the vector A.
		 */
		double length(void);

		/**
		 * Normalizes vector A.
		 */
		void normalize(void);

		/**
		 * Returns C = A x B, where A, B, and C are 3x3 vectors.
		 */
		void cross(const Vector* A, const Vector* B);

		/**
		 * Print vector A to stdout.
		 */
		void print(void);

		friend class Matrix;
		friend class SquareMatrix;

	public:
		double* m_data;

	protected:
		size_t  m_size;
	};
}

#endif
