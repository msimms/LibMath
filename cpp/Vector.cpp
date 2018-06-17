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
