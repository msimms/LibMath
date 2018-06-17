// by Michael J. Simms
// Copyright (c) 2011 Michael J. Simms
// All Rights Reserved

#include "Powers.h"

namespace LibMath
{
	unsigned long NearestPowerOf2(unsigned long num)
	{
		unsigned long n = num > 0 ? num - 1 : 0;
		
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 16;
		n++;
		
		return n;
	}
}
