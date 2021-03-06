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

#pragma once

#ifndef _DISTANCE_
#define _DISTANCE_

#include <stdlib.h>

namespace LibMath
{
	class Distance
	{
	public:
		/**
		 * Computes the Haversine distance between two points on Earth's surface.
		 */
		static double haversineDistance(double loc1_lat, double loc1_lon, double loc1_alt, double loc2_lat, double loc2_lon, double loc2_alt);

		/**
		 * Computes the Hamming distance of the strings.
		 */
		static size_t hammingDistance(const char* str1, const char* str2);
		
		/**
		 * Computes the Levenshtein distance of str2 relative to str1.
		 */
		static size_t levenshteinDistance(const char* str1, const char* str2);

		/**
		 * Computes the Euclidian distance between two points in a 1D space.
		 */
		static double euclidianDistance1D(double pt1, double pt2);
		
		/**
		 * Computes the Euclidian distance between two points in a 2D space.
		 */
		static double euclidianDistance2D(double pt1X, double pt1Y, double pt2X, double pt2Y);

	private:
		static double toRad(double deg);
	};
}

#endif
