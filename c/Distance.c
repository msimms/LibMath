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

size_t hammingDistance(const char* str1, const char* str2)
{
	size_t len1 = strlen(str1);

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

size_t levenshteinDistance(const char* str1, const char* str2)
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	
	if (len1 == 0)
		return len2;
	if (len2 == 0)
		return len1;

	size_t distance = 0;
	return distance;
}
