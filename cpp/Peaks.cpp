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

#include "Peaks.h"
#include "KMeans.h"
#include "Statistics.h"

#include <string.h>
#include <math.h>

namespace LibMath
{
	GraphPeakList Peaks::findPeaks(double* data, size_t dataLen, size_t* numPeaks)
	{
		std::vector<GraphPeak> peaks;
		
		GraphPeak currentPeak;
		
		double mean = Statistics::averageDouble(data, dataLen);
		double stddev = Statistics::standardDeviation(data, dataLen, mean);
		double oneSigma = mean + stddev;
		
		for (size_t x = 0; x < dataLen; ++x)
		{
			double y = data[x];
			
			if (y < oneSigma)
			{
				// Have we found a peak? If so, add it and start looking for the next one.
				if (currentPeak.rightTrough.x > 0)
				{
					// Compute the peak area.
					if (currentPeak.leftTrough.x < currentPeak.rightTrough.x)
					{
						for (size_t index = currentPeak.leftTrough.x + 1; index <= currentPeak.rightTrough.x; ++index)
						{
							double b = data[index] + data[index - 1];
							currentPeak.area += ((double)0.5 * b);
						}
					}
					
					peaks.push_back(currentPeak);
					currentPeak.clear();
				}
				
				// Are we looking for a left trough?
				else if (currentPeak.leftTrough.x == 0)
				{
					currentPeak.leftTrough.x = x;
					currentPeak.leftTrough.y = y;
				}
				
				// If we have a left trough and an existing peak, assume this is the right trough - for now.
				else if (currentPeak.peak.x > currentPeak.leftTrough.x)
				{					
					currentPeak.rightTrough.x = x;
					currentPeak.rightTrough.y = y;
				}
				
				else
				{
					currentPeak.clear();
				}
			}
			else
			{
				// Are we looking for a peak or is this bigger than the current peak?
				if (currentPeak.peak.x == 0 || y >= currentPeak.peak.y)
				{
					currentPeak.peak.x = x;
					currentPeak.peak.y = y;
				}
			}
		}
		
		return peaks;
	}
	
	GraphPeakList Peaks::findPeaks(const std::vector<double>& data)
	{
		std::vector<GraphPeak> peaks;
		
		GraphPeak currentPeak;
		
		double mean = Statistics::averageDouble(data);
		double stddev = Statistics::standardDeviation(data, mean);
		double oneSigma = mean + stddev;
		
		uint64_t x = 0;
		
		for (auto iter = data.begin(); iter < data.end(); ++iter, ++x)
		{
			double y = *iter;
			
			if (y < oneSigma)
			{
				// Have we found a peak? If so, add it and start looking for the next one.
				if (currentPeak.rightTrough.x > 0)
				{
					// Compute the peak area.
					if (currentPeak.leftTrough.x < currentPeak.rightTrough.x)
					{
						for (size_t index = currentPeak.leftTrough.x + 1; index <= currentPeak.rightTrough.x; ++index)
						{
							double b = data.at(index) + data.at(index - 1);
							currentPeak.area += ((double)0.5 * b);
						}
					}
					
					peaks.push_back(currentPeak);
					currentPeak.clear();
				}
				
				// Are we looking for a left trough?
				else if (currentPeak.leftTrough.x == 0)
				{
					currentPeak.leftTrough.x = x;
					currentPeak.leftTrough.y = y;
				}
				
				// If we have a left trough and an existing peak, assume this is the right trough - for now.
				else if (currentPeak.peak.x > currentPeak.leftTrough.x)
				{					
					currentPeak.rightTrough.x = x;
					currentPeak.rightTrough.y = y;
				}
				
				else
				{
					currentPeak.clear();
				}
			}
			else
			{
				// Are we looking for a peak or is this bigger than the current peak?
				if (currentPeak.peak.x == 0 || y >= currentPeak.peak.y)
				{
					currentPeak.peak.x = x;
					currentPeak.peak.y = y;
				}
			}
		}
		
		return peaks;
	}
	
	double Peaks::average(const GraphLine& data)
	{
		double sum = 0;
		
		for (auto iter = data.begin(); iter != data.end(); ++iter)
			sum = sum + (*iter).y;
		return sum / (double)data.size();
	}
	
	double Peaks::variance(const GraphLine& data, double mean)
	{
		double numerator = 0;
		
		for (auto iter = data.begin(); iter != data.end(); ++iter)
			numerator = numerator + (((*iter).y - mean) * ((*iter).y - mean));
		return numerator / (double)(data.size() - 1);
	}
	
	double Peaks::standardDeviation(const GraphLine& data, double mean)
	{
		double var = variance(data, mean);
		return sqrt(var);
	}
	
	GraphPeakList Peaks::findPeaks(const GraphLine& data)
	{
		std::vector<GraphPeak> peaks;
		
		GraphPeak currentPeak;
		
		double mean = average(data);
		double stddev = standardDeviation(data, mean);
		double oneSigma = mean + stddev;
		
		for (auto iter = data.begin(); iter < data.end(); ++iter)
		{
			const GraphPoint& pt = *iter;
			
			if (pt.y < oneSigma)
			{
				// Have we found a peak? If so, add it and start looking for the next one.
				if (currentPeak.rightTrough.x > 0)
				{
					// Compute the peak area.
					if (currentPeak.leftTrough.x < currentPeak.rightTrough.x)
					{
						auto pointIter = std::find(data.begin(), data.end(), currentPeak.leftTrough);
						if (pointIter != data.end())
						{
							GraphPoint prevPoint = (*pointIter);
							++pointIter;
							
							for (; pointIter != data.end(); ++pointIter)
							{
								double b = (*pointIter).y + prevPoint.y;
								currentPeak.area += ((double)0.5 * b);
								prevPoint = (*pointIter);
							}
						}
					}
					
					peaks.push_back(currentPeak);
					currentPeak.clear();
				}
				
				// Are we looking for a left trough?
				else if (currentPeak.leftTrough.x == 0)
				{
					currentPeak.leftTrough = pt;
				}
				
				// If we have a left trough and an existing peak, assume this is the right trough - for now.
				else if (currentPeak.peak.x > currentPeak.leftTrough.x)
				{					
					currentPeak.rightTrough = pt;
				}
				
				else
				{
					currentPeak.clear();
				}
			}
			else
			{
				// Are we looking for a peak or is this bigger than the current peak?
				if (currentPeak.peak.x == 0 || pt.y >= currentPeak.peak.y)
				{
					currentPeak.peak = pt;
				}
			}
		}
		
		return peaks;
	}
}