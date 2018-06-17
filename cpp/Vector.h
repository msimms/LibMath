// by Michael J. Simms
// Copyright (c) 1997-1998 Michael J. Simms
// All Rights Reserved

#pragma once

#ifndef _VECTOR_
#define _VECTOR_

namespace LibMath
{
	class Vector
	{
	public:
		Vector(int size);
		virtual ~Vector(void);

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
		
	protected:
		int     m_size;
		double* m_data;
	};
}

#endif
