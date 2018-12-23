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

#include <stdio.h>
#include <assert.h>

extern long long GetRDTSC(void);
extern unsigned long NearestPowerOf2(unsigned long num);

int main(int argc, const char * argv[])
{
	printf("Square Matrix Tests:\n");
	printf("--------------------\n");
	long long startTime = GetRDTSC();
	long long endTime = GetRDTSC();
	printf("Execution Time: %lld\n\n", endTime - startTime);

	printf("Statistics Tests:\n");
	printf("-----------------\n");
	startTime = GetRDTSC();
	endTime = GetRDTSC();
	printf("Execution Time: %lld\n\n", endTime - startTime);

	printf("Power Tests:\n");
	printf("------------\n");
	startTime = GetRDTSC();
	unsigned long nearest = NearestPowerOf2(63);
	endTime = GetRDTSC();
	printf("Nearest power of 2 for 63 is %ld.\n\n", nearest);
	assert(nearest == 64);
	printf("Execution Time: %lld\n\n", endTime - startTime);

	printf("Distance Tests:\n");
	printf("---------------\n");
	startTime = GetRDTSC();
	endTime = GetRDTSC();
	printf("Execution Time: %lld\n\n", endTime - startTime);

	return 0;
}
