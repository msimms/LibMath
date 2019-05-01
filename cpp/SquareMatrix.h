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

#include "Matrix.h"

namespace LibMath
{
	class SquareMatrix : public Matrix
	{
	public:
		SquareMatrix(size_t size);
		virtual ~SquareMatrix(void);

		/**
		 * Prints the matrix to standard out. Intended for testing and debugging.
		 */
		void print(void);

		/**
		 * Returns the number of elements in the matrix.
		 */		
		size_t size(void) const { return m_size; }

		/**
		 * Returns C = A x B, where A, B, and C are matrices.
		 */
		void multiply(const SquareMatrix* B, SquareMatrix* C);

		/**
		 * Returns C = A x B, where A is a matrix and B and C are vectors.
		 */
		void multiply(const Vector* B, Vector* C);

		/**
		 * Multiplies the matrix by the supplied scalar.
		 */
		void multiply(double B);

		/**
		 * Returns C = A - B, where A, B, and C are matrices.
		 */
		void subtract(const SquareMatrix* B, SquareMatrix* C);

		/**
		 * Subtracts the scalar from the matrix.
		 */
		void subtract(double B);

		/**
		 * Sets the value of A to the zero matrix.
		 */
		void zero(void);

		/**
		 * Sets the value of this matrix to the identity matrix.
		 */
		void identity(void);

		/**
		 * Sets the value of this matrix to the matrix of all ones.
		 */
		void ones(void);

		/**
		 * Returns the dot product of tthis matrix and B.
		 */
		double dot(const SquareMatrix* B);

	protected:
		size_t   m_size;

	protected:
		SquareMatrix();
	};
}

#endif
