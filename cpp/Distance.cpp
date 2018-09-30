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

#include "Distance.h"
#include "Statistics.h"
#include <string.h>
#include <math.h>

namespace LibMath
{
	double Distance::toRad(double deg)
	{
		const double pi = (double)(3.141592653589793238);
		return deg * (pi / (double)(180.0));
	}

	double Distance::haversineDistance(double loc1_lat, double loc1_lon, double loc1_alt, double loc2_lat, double loc2_lon, double loc2_alt)
	{
		double R = (double)6372797.560856; // radius of the earth in meters
		R += loc2_alt - loc1_alt;
		
		double latArc = toRad(loc1_lat - loc2_lat);
		double lonArc = toRad(loc1_lon - loc2_lon);
		
		double latH = sin(latArc * (double)0.5);
		latH *= latH;
		
		double lonH = sin(lonArc * (double)0.5);
		lonH *= lonH;
		
		double tmp = cos(toRad(loc1_lat)) * cos(toRad(loc2_lat));
		double rad = (double)2.0 * asin(sqrt(latH + tmp * lonH));
		
		return rad * R;
	}

	size_t Distance::hammingDistance(const char* str1, const char* str2)
	{
		size_t len1 = strlen(str1);

		// The strings must be the same length.
		if (len1 != strlen(str2))
			return (size_t)-1;
		
		size_t distance = 0;
		
		for (size_t i = 0; i < len1; ++i)
		{
			if (str1[i] != str2[i])
				++distance;
		}
		return distance;
	}

	size_t Distance::levenshteinDistance(const char* str1, const char* str2)
	{
		size_t m = strlen(str1);
		size_t n = strlen(str2);
		
		// Test for empty strings.
		if (m == 0)
			return n;
		if (n == 0)
			return m;
		
		// Temp vectors.
		size_t vecSize = sizeof(size_t) * n;
		size_t* v0 = (size_t*)malloc(vecSize);
		if (!v0)
		{
			return (size_t)-1;
		}
		size_t* v1 = (size_t*)malloc(vecSize);
		if (!v1)
		{
			free((void*)v0);
			return (size_t)-1;
		}
		size_t* tempV = (size_t*)malloc(vecSize);
		if (!tempV)
		{
			free((void*)v0);
			free((void*)v1);
			return (size_t)-1;
		}
		
		for (size_t i = 0; i < n; ++i)
		{
			v0[i] = i;
		}
		for (size_t i = 0; i < m - 1; ++i)
		{
			v1[0] = i + 1;
			
			for (size_t j = 0; j < n - 1; ++j)
			{
				size_t costs[3]; // deletion, insertion, and substitution costs (in that order)
				costs[0] = v0[j + 1] + 1;
				costs[1] = v1[j] + 1;
				if (str1[i] == str2[j])
					costs[2] = v0[j];
				else
					costs[2] = v0[j] + 1;
				v1[j + 1] = Statistics::min(costs, 3);
			}
			
			// Copy v1 to v0.
			memcpy(tempV, v0, vecSize);
			memcpy(v0, v1, vecSize);
			memcpy(v1, tempV, vecSize);
		}
		
		// Save the final distance calculation, before freeing the vector.
		size_t distance = v0[n - 1];
		
		// Clean up.
		free((void*)v0);
		free((void*)v1);
		free((void*)tempV);
		
		return distance;
	}

	double Distance::euclidianDistance1D(double pt1, double pt2)
	{
		return fabs(pt1 - pt2);
	}
	
	double Distance::euclidianDistance2D(double pt1X, double pt1Y, double pt2X, double pt2Y)
	{
		double tempX = pt2X - pt1X;
		double tempY = pt2Y - pt1Y;
		return sqrt((tempX * tempX) + (tempY * tempY));
	}
}
