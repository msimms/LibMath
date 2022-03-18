// by Michael J. Simms
// Copyright (c) 2022 Michael J. Simms

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

#include "Graphics.h"

#include <string.h>

namespace LibMath
{
	void QuadBezierFit2D(double in[][2], double out[][2], size_t numPoints, double t)
	{
		// Sanity check
		if (numPoints == 0)
		{
			return;
		}
		
		// If there's only one point, then just return it.
		if (numPoints == 1)
		{
			out[0][0] = in[0][0];
			out[0][1] = in[0][1];
			return;
		}

		// Copy the input matrix to the output matrix.
		memcpy(out, in, numPoints * sizeof(double) * 2);

		for (size_t i = numPoints - 1; i > 0; --i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				out[j][0] = out[j][0] + t * (out[j + 1][0] - out[j][0]);
				out[j][1] = out[j][1] + t * (out[j + 1][1] - out[j][1]);
			}
		}
	}

	void QuadBezierFit3D(double in[][3], double out[][3], size_t numPoints, double t)
	{
		// Sanity check
		if (numPoints == 0)
		{
			return;
		}
		
		// If there's only one point, then just return it.
		if (numPoints == 1)
		{
			out[0][0] = in[0][0];
			out[0][1] = in[0][1];
			out[0][2] = in[0][2];
			return;
		}
		
		// Copy the input matrix to the output matrix.
		memcpy(out, in, numPoints * sizeof(double) * 3);

		for (size_t i = numPoints - 1; i > 0; --i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				out[j][0] = out[j][0] + t * (out[j + 1][0] - out[j][0]);
				out[j][1] = out[j][1] + t * (out[j + 1][1] - out[j][1]);
				out[j][2] = out[j][2] + t * (out[j + 1][2] - out[j][2]);
			}
		}
	}
}
