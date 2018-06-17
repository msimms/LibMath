// by Michael J. Simms
// Copyright (c) 1997-1998 Michael J. Simms
// All Rights Reserved

#include <math.h>
#include <string.h>

#include "Vector.h"

namespace LibMath
{
	Vector::Vector(int size)
	{
		m_size = size;
		m_data = new double[m_size];
	}

	Vector::~Vector(void)
	{
		if (m_data != NULL)
		{
			delete m_data;
			m_data = NULL;
		}
	}

	void Vector::copy(const Vector* B)
	{
		memcpy((void *)m_data, (void *)B->m_data, sizeof(double) * m_size);
	}

	double Vector::multiply(const Vector* B)
	{
		register unsigned long i;
		double C = 0;

		// Compute C = A x B
		for (i = 0; i < m_size; i++)
			C += m_data[i] * B->m_data[i];

		// Return the result.
		return C;
	}

	void Vector::subtract(const Vector* B, Vector* C)
	{
		register unsigned long i;

		// Compute C = A - B
		for (i = 0; i < m_size; i++)
			C[i] = m_data[i] - B->m_data[i];
	}

	double Vector::dot(const Vector* B)
	{
		register unsigned long i;
		double result = 0.0;

		// Compute the dot product
		for (i = 0; i < m_size; i++)
			result += (m_data[i] * B->m_data[i]);

		// Return the result
		return result;
	}

	double Vector::length(void)
	{
		register int index;
		double sum = 0.0;

		for (index = 0; index < m_size; index++)
			sum += (m_data[index] * m_data[index]);
		return (sqrt(sum));
	}

	void Vector::normalize(void)
	{
		register int i;
		double norm;
		
		norm = length();
		for (i = 0; i < m_size; i++)
			m_data[i] = m_data[i] / norm;
	}

	void Vector::cross(const Vector* A, const Vector* B)
	{
		m_data[0] = (B->m_data[1] * A->m_data[2]) - (B->m_data[2] * A->m_data[1]);
		m_data[1] = (B->m_data[2] * A->m_data[0]) - (B->m_data[0] * A->m_data[2]);
		m_data[2] = (B->m_data[0] * A->m_data[1]) - (B->m_data[1] * A->m_data[0]);
	}
}
