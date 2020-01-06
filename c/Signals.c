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

#include <stdlib.h>
#include "Statistics.h"

// Smooths the data, which should be a list, by averaging with the given window size.
double* smooth(double* inData, size_t inDataLen, size_t windowSize)
{
	size_t outDataLen = inDataLen - windowSize + 1;
	if (outDataLen <= 0)
		return NULL;

	double* outData = malloc(sizeof(double) * outDataLen);
	for (size_t i = 0; i < outDataLen; ++i)
	{
		double val = statisticsAverageDouble(inData + i, windowSize);
		outData[i] = val;
	}
	return outData;
}
