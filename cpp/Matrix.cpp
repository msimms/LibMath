// by Michael J. Simms
// Copyright (c) 1997-1998 Michael J. Simms
// All Rights Reserved

#include <math.h>
#include <string.h>

#include "Matrix.h"

namespace LibMath
{
	Matrix::Matrix(int size)
	{
		register unsigned long i;
		
		m_size = size;
		m_data = new double *[m_size];
		for (i = 0; i < m_size; i++)
			m_data[i] = new double[m_size];
	}

	Matrix::~Matrix(void)
	{
		register unsigned long i;
		
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
		register unsigned long i, j, k;
		
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
		register unsigned long i, j;
		
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
		register unsigned long i, j;
		
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
		register unsigned long i, j;
		
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
		register unsigned long i, j;
		
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

	double Matrix::dot(const Matrix * B)
	{
		register unsigned long i, j;
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
