/*
 *  Powers.cpp
 *  MathLib
 *
 *  Created by Michael Simms on 4/24/11.
 *  Copyright 2011 Michael J. Simms. All rights reserved.
 *
 */

#include "Powers.h"

namespace MathLib
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
