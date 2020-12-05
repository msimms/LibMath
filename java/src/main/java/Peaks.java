//	MIT License
//
//  Copyright © 2019 Michael J Simms. All rights reserved.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

import java.util.*;

/**
 * <h1>Peaks</h1>
 * Implements peak finding algorithms.
 */
public class Peaks {

    /**
     * Constructor.
     */
    Peaks() {
    }

    /**
     * Computes the area of the specified peak.
     * 
     * @param data
     *             The x axis data comprising the entire line.
     * @param currentPeak
     *             The peak whose area is to be computed.
     */
	public static void computeArea(double[] data, GraphPeak currentPeak) {
		currentPeak.area = (double)0.0;
		
		if (currentPeak.leftTrough.x < currentPeak.rightTrough.x) {
			for (long index = currentPeak.leftTrough.x + 1; index <= currentPeak.rightTrough.x; ++index) {
				double b = data[(int)index] + data[(int)index - 1];
				currentPeak.area += ((double)0.5 * b);
			}
		}
	}
	
    /**
     * Returns all peaks in the graph line. A peak is defined as having a left trough, a peak,
     * a right trough, with the peak rising above a line defined by 'sigmas' standard deviations
     * above the mean.
     * 
     * @param data
     *             The point data comprising the entire line.
     * @param sigmas
     *             The number of standard deviations above which peak values will be considered.
     * @return An array of peak objects.
     */
	public static ArrayList<GraphPeak> findPeaks(double[] data, double sigmas) {
		ArrayList<GraphPeak> peaks = new ArrayList<GraphPeak>();
		
		GraphPeak currentPeak = new GraphPeak();
		
		double mean = Statistics.averageDouble(data);
		double stddev = sigmas * Statistics.standardDeviation(data, mean);
		double threshold = mean + stddev;
		
		for (long x = 0; x < data.length; ++x) {
			double y = data[(int)x];
			
			if (y < threshold) {
				// Have we found a peak? If so, add it and start looking for the next one.
				if (currentPeak.rightTrough.x > 0) {
					computeArea(data, currentPeak);
					peaks.add(currentPeak);
					currentPeak = new GraphPeak();
				}
				
				// Are we looking for a left trough?
				else if (currentPeak.leftTrough.x == 0) {
					currentPeak.leftTrough.x = x;
					currentPeak.leftTrough.y = y;
				}
				
				// If we have a left trough and an existing peak, assume this is the right trough - for now.
				else if ((currentPeak.peak.x > currentPeak.leftTrough.x) && (currentPeak.leftTrough.x > 0)) {
					currentPeak.rightTrough.x = x;
					currentPeak.rightTrough.y = y;
				}
				else {
					currentPeak.leftTrough.x = x;
					currentPeak.leftTrough.y = y;
				}
			}
			else if (currentPeak.leftTrough.x > 0) { // Left trough is set.
				// Are we looking for a peak or is this bigger than the current peak?
				if (currentPeak.peak.x == 0 || y >= currentPeak.peak.y) {
					currentPeak.peak.x = x;
					currentPeak.peak.y = y;
				}
			}
			else if (currentPeak.rightTrough.x > 0) { // Right trough is set.
				computeArea(data, currentPeak);
				peaks.add(currentPeak);
				currentPeak = new GraphPeak();
			}
			else { // Nothing is set, but the value is above the threshold.
				currentPeak.leftTrough.x = x;
				currentPeak.leftTrough.y = y;
			}
		}
		
		return peaks;
	}
	
    /**
     * Returns the average value of the specified points.
     * 
     * @param data
     *             The points whose areas are to be averaged.
     * @return The mean.
     */
	public static double average(ArrayList<GraphPoint> data) {
		double sum = (double)0.0;
		
        Iterator<GraphPoint> iter = data.iterator();
        while (iter.hasNext()) { 
			GraphPoint pt = iter.next();
			sum = sum + pt.y;
        }
		return sum / (double)data.size();
	}
	
    /**
     * Returns the variance of the specified points.
     * 
     * @param data
     *             The points whose areas are to be averaged.
     * @param mean
     *             The mean value of the given points.
     * @return The variance.
     */
	public static double variance(ArrayList<GraphPoint> data, double mean) {
		double numerator = (double)0.0;
		
        Iterator<GraphPoint> iter = data.iterator();
        while (iter.hasNext()) { 
			GraphPoint pt = iter.next();
			numerator = numerator + ((pt.y - mean) * (pt.y - mean));
        }
		return numerator / (double)(data.size() - 1);
	}
	
    /**
     * Returns the standard deviation of the specified points.
     * 
     * @param data
     *             The points whose areas are to be averaged.
     * @param mean
     *             The mean value of the given points.
     * @return The standard deviation.
     */
	public static double standardDeviation(ArrayList<GraphPoint> data, double mean) {
		double var = variance(data, mean);
		return Math.sqrt(var);
	}
	
    /**
     * Computes the area of the specified peak.
     * 
     * @param data
     *             The point data comprising the entire line.
     * @param currentPeak
     *             The peak whose area is to be computed.
     */
	public static void computeArea(ArrayList<GraphPoint> data, GraphPeak currentPeak) {
		currentPeak.area = (double)0.0;
		
		if (currentPeak.leftTrough.x < currentPeak.rightTrough.x) {
            int leftIndex = data.indexOf(currentPeak.leftTrough);
            Iterator<GraphPoint> pointIter = data.listIterator(leftIndex);

            if (pointIter.hasNext()) { 
                GraphPoint prevPoint = pointIter.next();
                GraphPoint currPoint = pointIter.next();
				
				while (pointIter.hasNext()) {
					double b = currPoint.y + prevPoint.y;
					currentPeak.area += ((double)0.5 * b);
                    prevPoint = currPoint;
                    currPoint = pointIter.next();
				}
			}
		}
	}
    
    /**
     * Returns all peaks above a certain area. A peak is defined as having a left trough, a peak,
     * a right trough, with the peak rising above a line defined by 'sigmas' standard deviations
     * above the mean.
     * 
     * @param data
     *             The point data comprising the entire line.
     * @param minPeakArea
     *             All peaks greater than or equal to this will be appended to the output.
     * @param sigmas
     *             The number of standard deviations above which peak values will be considered.
     * @return An array of peak objects.
     */
	public static ArrayList<GraphPeak> findPeaksOfSize(ArrayList<GraphPoint> data, double minPeakArea, double sigmas) {
		ArrayList<GraphPeak> peaks = new ArrayList<GraphPeak>();
		
		GraphPeak currentPeak = new GraphPeak();
		
		double mean = average(data);
		double stddev = sigmas * standardDeviation(data, mean);
		double threshold = mean + stddev;
		
        Iterator<GraphPoint> iter = data.iterator();
        while (iter.hasNext()) { 
			GraphPoint pt = iter.next();
			
			if (pt.y < threshold) {
				// Have we found a peak? If so, add it and start looking for the next one.
				if (currentPeak.rightTrough.x > 0) { // Right trough is set
					computeArea(data, currentPeak);
					if (currentPeak.area >= minPeakArea) {
						peaks.add(currentPeak);
					}
					currentPeak = new GraphPeak();
				}
				
				// Are we looking for a left trough?
				else if (currentPeak.leftTrough.x == 0) { // Left trough is not set.
					currentPeak.leftTrough = pt;
				}
				
				// If we have a left trough and an existing peak, assume this is the right trough - for now.
				else if ((currentPeak.peak.x > currentPeak.leftTrough.x) && (currentPeak.leftTrough.x > 0)) {
					currentPeak.rightTrough = pt;
				}
				else {
					currentPeak.leftTrough = pt;
				}
			}
			else if (currentPeak.leftTrough.x > 0) { // Left trough is set.
				// Are we looking for a peak or is this bigger than the current peak, making it the real peak?
				if (currentPeak.peak.x == 0 || pt.y >= currentPeak.peak.y) {
					currentPeak.peak = pt;
				}
			}
			else if (currentPeak.rightTrough.x > 0) { // Right trough is set.
				computeArea(data, currentPeak);
				if (currentPeak.area >= minPeakArea) {
					peaks.add(currentPeak);
				}
				currentPeak = new GraphPeak();
			}
			else { // Nothing is set, but the value is above the threshold.
				currentPeak.leftTrough = pt;
			}
		}
		
		return peaks;
	}
}
