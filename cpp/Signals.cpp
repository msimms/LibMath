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

#include "Signals.h"
#include "Statistics.h"

namespace LibMath
{
	// Smooths the data, which should be a list, by averaging with the given window size.
	std::vector<double> Signals::smooth(const std::vector<double>& inData, size_t windowSize)
	{
		std::vector<double> outData;

		size_t outDataLen = inData.size() - windowSize + 1;
		if (outDataLen <= 0)
			return outData;

		size_t i = 0;
		for (auto iter = inData.begin(); i < outDataLen && iter != inData.end(); ++i, ++iter)
		{
			std::vector<double> tempData(inData.begin() + i, inData.begin() + i + windowSize);
			double val = Statistics::averageDouble(tempData);
			outData.push_back(val);
		}
		return outData;
	}
}
