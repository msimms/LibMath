// by Michael J. Simms
// Copyright (c) 1997-1998 Michael J. Simms
// All Rights Reserved

#pragma once

#ifndef _MATRIX_
#define _MATRIX_

#include "Vector.h"

namespace LibMath
{
	class Matrix
	{
	public:
		Matrix(int size);
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
		int      m_size;
		double** m_data;
	};
}

#endif
