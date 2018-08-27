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
		
		if (len1 != strlen(str2))
			return (size_t)-1;
		
		size_t distance = 0;
		
		for (size_t i = 0; i < len1; ++i)
		{
			if (str1[i] == str2[i])
				++distance;
		}
		return distance;
	}

	size_t Distance::levenshteinDistance(const char* str1, const char* str2)
	{
		size_t distance = 0;
		return distance;
	}
}

