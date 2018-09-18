// Created by Michael Simms on 6/17/18.
// Copyright (c) 2018 Michael Simms. All rights reserved.

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

#include <iostream>
#include "Distance.h"
#include "Powers.h"
#include "SquareMatrix.h"
#include "Statistics.h"

int main(int argc, const char * argv[])
{
	std::cout << "Square Matrix Tests:" << std::endl;
	std::cout << "--------------------" << std::endl;

	LibMath::SquareMatrix* m = new LibMath::SquareMatrix(5);
	m->identity();
	std::cout << "Identity matrix:" << std::endl;
	m->print();
	delete m;

	m = new LibMath::SquareMatrix(5);
	m->zero();
	std::cout << "Zero matrix:" << std::endl;
	m->print();
	m->ones();
	std::cout << "Ones matrix:" << std::endl;
	m->print();
	m->multiply(2.0);
	std::cout << "Ones matrix multiplied by 2.0:" << std::endl;
	m->print();
	delete m;

	std::cout << "Statistics Tests:" << std::endl;
	std::cout << "-----------------" << std::endl;

	long v_int[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double v_int_avg = LibMath::Statistics::averageLong(v_int, 9);
	std::cout << "Average: " << v_int_avg << std::endl;
	assert(v_int_avg == 5.0);
	double v_flt[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	double v_flt_avg = LibMath::Statistics::averageDouble(v_flt, 9);
	std::cout << "Average: " << v_flt_avg << std::endl;
	assert(v_flt_avg == 5.0);
	double variance = LibMath::Statistics::variance(v_flt, 9, v_flt_avg);
	std::cout << "Variance: " << variance << std::endl;
	assert(variance == 7.5);
	std::cout << "Standard Deviation: " << LibMath::Statistics::standardDeviation(v_flt, 9, v_flt_avg) << std::endl;
	double max = LibMath::Statistics::max(v_flt, 9);
	std::cout << "Max: " << max << std::endl;
	assert(max == 9.0);
	double min = LibMath::Statistics::min(v_flt, 9);
	std::cout << "Min: " << min << std::endl << std::endl;
	assert(min == 1.0);

	std::cout << "Power Tests:" << std::endl;
	std::cout << "------------" << std::endl;

	unsigned long nearest = LibMath::NearestPowerOf2(63);
	std::cout << "Nearest power of 2 for 63 is " << nearest << "." << std::endl << std::endl;
	assert(nearest == 64);

	std::cout << "Distance Tests:" << std::endl;
	std::cout << "---------------" << std::endl;

	size_t distance = LibMath::Distance::hammingDistance("1011101", "1001001");
	std::cout << "Hamming Distance: " << distance << std::endl << std::endl;
	assert(distance == 2);
	
	return 0;
}
