// by Michael J. Simms
// Copyright (c) 2018 Michael J. Simms

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

#include "Matrix.h"

#include <iostream>

namespace LibMath
{
	Matrix::Matrix()
	{
		m_w = 0;
		m_h = 0;
		m_data = NULL;
	}

	Matrix::Matrix(size_t w, size_t h)
	{
		m_w = w;
		m_h = h;
		m_data = new double *[w];
		for (auto i = 0; i < h; ++i)
			m_data[i] = new double[h];
	}

	Matrix::~Matrix()
	{
		if (m_data != NULL)
		{
			for (auto i = 0; i < m_w; ++i)
			{
				delete m_data[i];
				m_data[i] = NULL;
			}
			delete m_data;
			m_data = NULL;
		}
	}

	void Matrix::print(void)
	{
		if (m_data != NULL)
		{
			for (auto i = 0; i < m_w; ++i)
			{
				std::cout << "[ ";
				for (auto j = 0; j < m_h; ++j)
				{
					std::cout << m_data[i][j] << " ";
				}
				std::cout << "]" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void Matrix::multiply(const Matrix* B, Vector* C)
	{
		for (auto i = 0; i < m_w; ++i)
		{
			for (auto j = 0; j < m_h; ++j)
			{
				C->m_data[i] = this->m_data[i][j] * B->m_data[j][i];
			}
		}
	}

	void Matrix::multiply(double B)
	{
		for (auto i = 0; i < m_w; ++i)
		{
			for (auto j = 0; j < m_h; ++j)
			{
				m_data[i][j] *= B;
			}
		}
	}

	void Matrix::subtract(const Matrix* B, Matrix* C)
	{
		for (auto i = 0; i < m_w; ++i)
		{
			for (auto j = 0; j < m_h; ++j)
			{
				C->m_data[i][j] = this->m_data[i][j] - B->m_data[i][j];
			}
		}
	}

	void Matrix::subtract(double B)
	{
		for (auto i = 0; i < m_w; ++i)
		{
			for (auto j = 0; j < m_h; ++j)
			{
				m_data[i][j] -= B;
			}
		}
	}

	void Matrix::zero(void)
	{
		for (auto i = 0; i < m_w; ++i)
		{
			for (auto j = 0; j < m_h; ++j)
			{
				m_data[i][j] = 0.0;
			}
		}
	}
}
