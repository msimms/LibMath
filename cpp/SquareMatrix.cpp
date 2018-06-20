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

#include <math.h>
#include <iostream>

#include "SquareMatrix.h"

namespace LibMath
{
	SquareMatrix::SquareMatrix() : Matrix()
	{
		m_size = 0;
		m_data = NULL;
	}

	SquareMatrix::SquareMatrix(size_t size) : Matrix(size, size)
	{
		m_size = size;
		m_data = new double *[m_size];
		for (auto i = 0; i < m_size; ++i)
			m_data[i] = new double[m_size];
	}

	SquareMatrix::~SquareMatrix(void)
	{
		if (m_data != NULL)
		{
			for (auto i = 0; i < m_size; ++i)
			{
				delete m_data[i];
				m_data[i] = NULL;
			}
			delete m_data;
			m_data = NULL;
		}
	}

	void SquareMatrix::print(void)
	{
		if (m_data != NULL)
		{
			for (auto i = 0; i < m_size; ++i)
			{
				std::cout << "[ ";
				for (auto j = 0; j < m_size; ++j)
				{
					std::cout << m_data[i][j] << " ";
				}
				std::cout << "]" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void SquareMatrix::multiply(const SquareMatrix* B, SquareMatrix* C)
	{
		// Compute C = A x B
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				C->m_data[i][j] = 0.0;
				for (auto k = 0; k < m_size; ++k)
				{
					C->m_data[i][j] += m_data[i][k] * B->m_data[k][j];
				}
			}
		}
	}

	void SquareMatrix::multiply(const Vector* B, Vector* C)
	{
		// Compute C = A x B
		for (auto i = 0; i < m_size; ++i)
		{
			C->m_data[i] = 0.0;
			for (auto j = 0; j < m_size; ++j)
			{
				C->m_data[i] += m_data[i][j] * B->m_data[j];
			}
		}
	}

	void SquareMatrix::multiply(double B)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				m_data[i][j] *= B;
			}
		}
	}

	void SquareMatrix::subtract(const SquareMatrix* B, SquareMatrix* C)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				C->m_data[i][j] = m_data[i][j] - B->m_data[i][j];
			}
		}
	}

	void SquareMatrix::subtract(double B)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				m_data[i][j] -= B;
			}
		}
	}

	void SquareMatrix::zero(void)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				m_data[i][j] = 0.0;
			}
		}
	}

	void SquareMatrix::identity(void)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				if (i == j)
					m_data[i][j] = 1.0;
				else
					m_data[i][j] = 0.0;
			}
		}
	}
	
	void SquareMatrix::ones(void)
	{
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				m_data[i][j] = 1.0;
			}
		}
	}
	
	double SquareMatrix::dot(const SquareMatrix* B)
	{
		double dot = 0.0;
		
		for (auto i = 0; i < m_size; ++i)
		{
			for (auto j = 0; j < m_size; ++j)
			{
				dot +=	*(m_data[i] + j * m_size) + *(B->m_data[i] + j * B->m_size);
			}
		}
		return dot;
	}
}
