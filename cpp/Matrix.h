// by Michael J. Simms
// Copyright (c) 1997-1998 Michael J. Simms

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

#ifndef _MATRIX_
#define _MATRIX_

#include "Vector.h"

namespace LibMath
{
	class Matrix
	{
	public:
		Matrix(size_t size);
		virtual ~Matrix(void);

		/**
		 * Returns C = A x B, where A, B, and C are matrices.
		 */
		void multiply(const Matrix* B, Matrix* C);

		/**
		 * Returns C = A x B, where A is a matrix and B and C are vectors.
		 */
		void multiply(const Vector* B, Vector* C);

		/**
		 * Returns C = A - B, where A, B, and C are matrices.
		 */
		void subtract(const Matrix* B, Matrix* C);

		/**
		 * Sets the value of A to the zero matrix.
		 */
		void zero(void);

		/**
		 * Sets the value of A to the identity matrix.
		 */
		void identity(void);

		/**
		 * Returns the dot product of A (the current matrix) and B.
		 */
		double dot(const Matrix* B);
		
	protected:
		size_t   m_size;
		double** m_data;
	};
}

#endif
