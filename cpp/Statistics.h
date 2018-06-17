// by Michael J. Simms
// Copyright (c)1998 Michael J. Simms
// All Rights Reserved

#pragma once

#ifndef _STATISTICS_
#define _STATISTICS_

class Statistics
{	
public:
	// Computes the average value in the given array.
	static double averageLong(const long* data, unsigned long numPoints);
	
	// Computes the average value in the given array.
	static double averageDouble(const double* data, unsigned long numPoints);
	
	// Computes the variance of the given array
	// with the mean value supplied.
	static double variance(const double* data, unsigned long numPoints, double mean);
	
	// Computes the standard deviation of the given array
	// with the mean value supplied.
	static double standardDeviation(const double* data, unsigned long numPoints, double mean);
	
	// Finds the largest value in the array.
	static double max(const double* data, unsigned long numPoints);
	
	// Finds the smallest value in the array.
	static double min(const double* data, unsigned long numPoints);
};

#endif
