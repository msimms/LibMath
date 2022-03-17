// by Michael J. Simms
// Copyright (c) 2020 Michael J. Simms

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

#ifndef _SIGNALS_
#define _SIGNALS_

#include <vector>

namespace LibMath
{
	class Signals
	{	
	public:
		/**
		 * Smooths the data by averaging points with the given window size.
		 * Returns the number of points written to 'outData'.
		 **/
		static size_t smooth(const double* inData, double* outData, size_t numPoints, size_t windowSize);

		/**
		 * Smooths the data, which should be a list, by averaging with the given window size.
		 **/
		static std::vector<double> smooth(const std::vector<double>& inData, size_t windowSize);
	};
}

#endif
