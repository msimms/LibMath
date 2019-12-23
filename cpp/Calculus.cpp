// by Michael J. Simms
// Copyright (c) 2019 Michael J. Simms

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

#include "Calculus.h"

namespace LibMath
{
    void derivative(double* in, double* out, size_t inLen, size_t spacing)
    {
        if (spacing >= 1)
        {
            for (size_t i = 0; i < inLen - spacing; i += spacing)
            {
                out[i] = (in[i + spacing] - in[i]) / spacing;
            }
        }
    }

	std::vector<double> derivative(std::vector<double> in, size_t spacing)
	{
		std::vector<double> result;

        if (spacing >= 1)
        {
			auto iter = in.begin();
			double lastY = (*iter);
			std::next(iter, spacing);

			while (iter != in.end())
			{
				double currY = (*iter);
				double val = (currY - lastY) / (double)spacing;
				result.push_back(val);
				std::next(iter, spacing);
			}
		}
		return result;
	}

	double integral(double* data, size_t dataLen)
    {
        double area = (double)0.0;

        if (dataLen > 1)
        {
            for (size_t i = 1; i < dataLen; ++i)
            {
                double b = data[i] + data[i - 1];
                area += ((double)0.5 * b);
            }
        }
        return area;
    }
}
