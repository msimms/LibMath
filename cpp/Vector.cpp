// by Michael J. Simms
// Copyright (c)1997-1998 Michael J. Simms
// All Rights Reserved

#include <math.h>
#include <string.h>

#include "Vector.h"

// ---------------------------------------------------------------------------
// Constructor, requires designating the length of the vector.
// ---------------------------------------------------------------------------
Vector::Vector(int size)
{
	m_size = size;
	m_data = new double[m_size];
}

// ---------------------------------------------------------------------------
// Default destructor.
// ---------------------------------------------------------------------------
Vector::~Vector(void)
{
	if (m_data != NULL)
		delete m_data;
}

// ---------------------------------------------------------------------------
// Returns a copy of vector B in vector A.
// ---------------------------------------------------------------------------
void Vector::copy(const Vector* B)
{
	memcpy((void *)m_data, (void *)B->m_data, sizeof(double) * m_size);
}

// ---------------------------------------------------------------------------
// Returns C = A x B, where A and B are vectors and C is a scalar.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Returns C = A - B, where A, B, and C are vectors.
// ---------------------------------------------------------------------------
void Vector::subtract(const Vector* B, const Vector* C)
{
	register unsigned long i;
	
	// Compute C = A - B
	for (i = 0; i < m_size; i++)
		C[i] = m_data[i] - B->m_data[i];
}

// ---------------------------------------------------------------------------
// Returns the dot product of A and B, where A and B are vectors.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Computes the length of the vector A.
// ---------------------------------------------------------------------------
double Vector::length(void)
{
	register int index;
	double sum = 0.0;
	
	for (index = 0; index < m_size; index++)
		sum += (m_data[index] * m_data[index]);
	return (sqrt(sum));
}

// ---------------------------------------------------------------------------
// Normalizes vector A.
// ---------------------------------------------------------------------------
void Vector::normalize(void)
{
	register int i;
	double norm;
	
	norm = length();
	for (i = 0; i < m_size; i++)
		m_data[i] = m_data[i] / norm;
}

// ---------------------------------------------------------------------------
// Returns C = A x B, where A, B, and C are 3x3 vectors.
// ---------------------------------------------------------------------------
void Vector::cross(const Vector* A, const Vector* B)
{
	m_data[0] = (B->m_data[1] * A->m_data[2]) - (B->m_data[2] * A->m_data[1]);
	m_data[1] = (B->m_data[2] * A->m_data[0]) - (B->m_data[0] * A->m_data[2]);
	m_data[2] = (B->m_data[0] * A->m_data[1]) - (B->m_data[1] * A->m_data[0]);
}
