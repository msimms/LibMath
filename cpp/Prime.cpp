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

#include "Prime.h"
#include <math.h>
#include <stdlib.h>

namespace LibMath
{
	uint64_t Prime::gcd(uint64_t a, uint64_t b)
	{
		if (a == 0)
			return b;
		if (b == 0)
			return a;
		uint64_t r = a % b;
		return gcd(b, r);
	}
	
	uint64_t Prime::randOdd(uint64_t a)
	{
		size_t b = rand() % (a - 2);
		if ((b & 1) == 0)
			++b;
		return b;
	}

	uint64_t Prime::generateCoprime(uint64_t a)
	{
		while (true)
		{
			size_t b = 1 + randOdd(a - 1); // random number between 1 and a - 1
			if ((b & 1) == 0)
				++b;
			if (gcd(a, b) == 1)
				return b;
		}
		return 1;
	}

	bool Prime::isPrimeFermat(uint64_t num)
	{
		// If the first test succeeds, then do a second test, to make sure we don't have a Fermat liar.
		for (size_t i = 0; i < 2; ++i)
		{
			size_t n = generateCoprime(num);
			uint64_t temp = pow(n, num - 1);
			if (temp % num != 1)
				return false;
		}

		return true;
	}

	bool Prime::isPrimeMillerRabin(uint64_t num)
	{
//		size_t a = 2 + rand() % (num - 4); // random int in range [2, num - 2]
		return false;
	}
}
