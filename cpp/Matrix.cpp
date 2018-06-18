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

#include "Matrix.h"

namespace LibMath
{
	Matrix::Matrix(size_t size)
	{
		register size_t i;
		
		m_size = size;
		m_data = new double *[m_size];
		for (i = 0; i < m_size; i++)
			m_data[i] = new double[m_size];
	}

	Matrix::~Matrix(void)
	{
		register size_t i;
		
		if (m_data != NULL)
		{
			for (i = 0; i < m_size; i++)
			{
				delete m_data[i];
				m_data[i] = NULL;
			}
			delete m_data;
			m_data = NULL;
		}
	}

	void Matrix::multiply(const Matrix * B, Matrix * C)
	{
		register size_t i, j, k;
		
		// Compute C = A x B
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				C->m_data[i][j] = 0.0;
				for (k = 0; k < m_size; k++)
				{
					C->m_data[i][j] += m_data[i][k] * B->m_data[k][j];
				}
			}
		}
	}

	void Matrix::multiply(const Vector * B, Vector * C)
	{
		register size_t i, j;
		
		// Compute C = A x B
		for (i = 0; i < m_size; i++)
		{
			C->m_data[i] = 0.0;
			for (j = 0; j < m_size; j++)
			{
				C->m_data[i] += m_data[i][j] * B->m_data[j];
			}
		}
	}

	void Matrix::subtract(const Matrix * B, Matrix * C)
	{
		register size_t i, j;
		
		// Compute C = A - B
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				C->m_data[i][j] = m_data[i][j] - B->m_data[i][j];
			}
		}
	}

	void Matrix::zero(void)
	{
		register size_t i, j;
		
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				m_data[i][j] = 0.0;
			}
		}
	}

	void Matrix::identity(void)
	{
		register size_t i, j;
		
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				if (i == j)
					m_data[i][j] = 1.0;
				else
					m_data[i][j] = 0.0;
			}
		}
	}
	
	void Matrix::ones(void)
	{
		register size_t i, j;
		
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				m_data[i][j] = 1.0;
			}
		}
	}
	
	double Matrix::dot(const Matrix * B)
	{
		register size_t i, j;
		double dot = 0.0;
		
		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < m_size; j++)
			{
				dot +=	*(m_data[i] + j * m_size) +
				*(B->m_data[i] + j * B->m_size);
			}
		}
		return dot;
	}
}
