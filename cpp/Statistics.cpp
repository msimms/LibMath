// by Michael J. Simms
// Copyright (c) 1998 Michael J. Simms
// All Rights Reserved

#include <math.h>

#include "Statistics.h"

namespace LibMath
{
	double Statistics::averageLong(const long* data, unsigned long numPoints)
	{
		register long index;
		register long sum = 0;

		for (index = 0; index < numPoints; index++)
			sum = sum + data[index];
		return (double)sum / (double)numPoints;
	}

	double Statistics::averageDouble(const double* data, unsigned long numPoints)
	{
		register long	index;
		register double	sum = 0;

		for (index = 0; index < numPoints; index++)
			sum = sum + data[index];
		return sum / (double)numPoints;
	}

	double Statistics::variance(const double* data, unsigned long numPoints, double mean)
	{
		register long	index;
		register double	numerator = 0;
		
		for (index = 0; index < numPoints; index++)
			numerator = numerator + ((data[index] - mean) * (data[index] - mean));
		return numerator / (double)(numPoints - 1);
	}

	double Statistics::standardDeviation(const double* data, unsigned long numPoints, double mean)
	{
		double var = variance(data, numPoints, mean);
		return sqrt(var);
	}

	double Statistics::max(const double* data, unsigned long numPoints)
	{
		register long	index;
		register double	result = data[0];
		
		for (index = 1; index < numPoints; index++)
		{
			if (data[index] > result)
				result = data[index];
		}
		return result;
	}

	double Statistics::min(const double* data, unsigned long numPoints)
	{
		register long	index;
		register double	result = data[0];
		
		for (index = 1; index < numPoints; index++)
		{
			if (data[index] < result)
				result = data[index];
		}
		return result;
	}
}
