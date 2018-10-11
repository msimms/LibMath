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
#include <fstream>
#include <sstream>
#include <vector>

#include "Distance.h"
#include "KMeans.h"
#include "Peaks.h"
#include "Powers.h"
#include "SquareMatrix.h"
#include "Statistics.h"

typedef std::vector<double> NumVec;

std::vector<NumVec> readCsv(const std::string& fileName)
{
	std::vector<NumVec> columns;
	std::vector<double> tsList, xList, yList, zList;

	std::string line;
	std::ifstream infile(fileName);
	while (std::getline(infile, line, '\n'))
	{
		std::istringstream iss(line);
		std::string value;
		uint64_t ts = 0;
		double x = 0.0, y = 0.0, z = 0.0;

		iss >> ts;
		iss.ignore(256, ',');
		iss >> x;
		iss.ignore(256, ',');
		iss >> y;
		iss.ignore(256, ',');
		iss >> z;

		tsList.push_back(ts);
		xList.push_back(x);
		yList.push_back(y);
		zList.push_back(z);
	}

	columns.push_back(tsList);
	columns.push_back(xList);
	columns.push_back(yList);
	columns.push_back(zList);
	return columns;
}

int main(int argc, const char * argv[])
{
	const std::string OPTION_CSV_FILE = "--csv";

	std::string csvFileName;
	
	for (size_t i = 1; i < argc; ++i)
	{
		if ((OPTION_CSV_FILE.compare(argv[i]) == 0) && (i + 1 < argc))
		{
			csvFileName = argv[++i];
		}
	}

	std::cout << "Square Matrix Tests:" << std::endl;
	std::cout << "--------------------" << std::endl;

	LibMath::SquareMatrix* m = new LibMath::SquareMatrix(5);
	if (m)
	{
		m->identity();
		std::cout << "Identity matrix:" << std::endl;
		m->print();
		delete m;
	}

	m = new LibMath::SquareMatrix(5);
	if (m)
	{
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
	}

	std::cout << "Statistics Tests:" << std::endl;
	std::cout << "-----------------" << std::endl;

	long v_int[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double v_int_avg = LibMath::Statistics::averageLong(v_int, 9);
	std::cout << "Average: " << v_int_avg << std::endl;
	assert(v_int_avg == 5.0);
	std::vector<long> v_int2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	v_int_avg = LibMath::Statistics::averageLong(v_int2);
	std::cout << "Average: " << v_int_avg << std::endl;
	assert(v_int_avg == 5.0);
	double v_flt[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	double v_flt_avg = LibMath::Statistics::averageDouble(v_flt, 9);
	std::cout << "Average: " << v_flt_avg << std::endl;
	assert(v_flt_avg == 5.0);
	std::vector<double> v_flt2 = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	v_flt_avg = LibMath::Statistics::averageDouble(v_flt2);
	std::cout << "Average: " << v_flt_avg << std::endl;
	assert(v_flt_avg == 5.0);
	double variance = LibMath::Statistics::variance(v_flt, 9, v_flt_avg);
	std::cout << "Variance: " << variance << std::endl;
	assert(variance == 7.5);
	variance = LibMath::Statistics::variance(v_flt2, v_flt_avg);
	std::cout << "Variance: " << variance << std::endl;
	assert(variance == 7.5);
	std::cout << "Standard Deviation: " << LibMath::Statistics::standardDeviation(v_flt, 9, v_flt_avg) << std::endl;
	std::cout << "Standard Deviation: " << LibMath::Statistics::standardDeviation(v_flt2, v_flt_avg) << std::endl;
	double max = LibMath::Statistics::max(v_flt, 9);
	std::cout << "Max: " << max << std::endl;
	assert(max == 9.0);
	max = LibMath::Statistics::max(v_flt2);
	std::cout << "Max: " << max << std::endl;
	assert(max == 9.0);
	double min = LibMath::Statistics::min(v_flt, 9);
	std::cout << "Min: " << min << std::endl;
	assert(min == 1.0);
	min = LibMath::Statistics::min(v_flt2);
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
	std::cout << "Hamming Distance: " << distance << std::endl;
	assert(distance == 2);
	distance = LibMath::Distance::levenshteinDistance("foo", "foobar");
	std::cout << "Levenshtein Distance: " << distance << std::endl << std::endl;
	assert(distance == 3);

	std::cout << "K-Means Tests:" << std::endl;
	std::cout << "--------------" << std::endl;

	double kMeansIn[10];
	kMeansIn[0] = 7.123;
	kMeansIn[1] = 0.999;
	kMeansIn[2] = 0.001;
	kMeansIn[3] = 0.5;
	kMeansIn[4] = 0.75;
	kMeansIn[5] = 0.002;
	kMeansIn[6] = 3.0;
	kMeansIn[7] = 2.0;
	kMeansIn[8] = 5.0;
	kMeansIn[9] = 0.001;
	size_t* tags = LibMath::KMeans::withEquallySpacedCentroids1D(kMeansIn, 10, 3, (double)0.001, 3);
	if (tags)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			std::cout << tags[i] << std::endl;
		}
		delete tags;
	}
	std::cout << std::endl;

	if (csvFileName.length() > 0)
	{
		std::cout << "Peak Finding Tests:" << std::endl;
		std::cout << "-------------------" << std::endl;
		
		std::vector<NumVec> csvData = readCsv(csvFileName);
		auto csvIter = csvData.begin();
		++csvIter; // Skip over the timestamp column
		uint16_t axisCount = 0;
		for (; csvIter != csvData.end(); ++csvIter)
		{
			std::cout << "Axis " << ++axisCount << ":" << std::endl;

			NumVec& columnData = (*csvIter);
			uint64_t peakCount = 0;
			std::vector<LibMath::GraphPeak> peaks = LibMath::Peaks::findPeaks(columnData);
			for (auto peakIter = peaks.begin(); peakIter != peaks.end(); ++peakIter)
			{
				LibMath::GraphPeak& peak = (*peakIter);
				std::cout << "Peak " << ++peakCount << ": {" << peak.leftTrough.x << ", " << peak.peak.x << ", " << peak.rightTrough.x << ", " << peak.area << "}" << std::endl;
			}
			std::cout << std::endl;
		}
	}

	return 0;
}
