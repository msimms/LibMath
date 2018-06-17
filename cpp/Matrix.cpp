// by Michael J. Simms
// Copyright (c)1997-1998 Michael J. Simms
// All Rights Reserved

#include <math.h>
#include <string.h>

#include "Matrix.h"

// ---------------------------------------------------------------------------
// Constructor, requires designating the size of the square matrix.
// ---------------------------------------------------------------------------
Matrix::Matrix(int size)
{
	register unsigned long i;
	
	m_size = size;
	m_data = new double *[m_size];
	for (i = 0; i < m_size; i++)
		m_data[i] = new double[m_size];
}

// ---------------------------------------------------------------------------
// Default destructor.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Returns C = A x B, where A, B, and C are matrices.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Returns C = A x B, where A is a matrix and B and C are vectors.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Returns C = A - B, where A, B, and C are matrices.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Sets the value of A to the zero matrix.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Sets the value of A to the identity matrix.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Returns the dot product of A (the current matrix) and B.
// ---------------------------------------------------------------------------
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

