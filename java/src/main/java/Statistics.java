// by Michael J. Simms
// Copyright (c) 2019 Michael J. Simms

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

/**
 * <h1>Statistics</h1>
 * Implements basic statistical functions.
 */
public class Statistics {

    /**
     * Constructor.
     */
    Statistics() {
    }

	public static double averageLong(long[] data) {
		long sum = 0;

		for (int index = 0; index < data.length; index++)
			sum = sum + data[index];
		return (double)sum / (double)data.length;
	}

	public static double averageDouble(double[] data) {
		double sum = 0;

		for (int index = 0; index < data.length; index++)
			sum = sum + data[index];
		return sum / (double)data.length;
	}

	public static double[] noramlize(double[] data, double mean, double variance) {
        double[] normalized = new double[data.length];
		for (int index = 0; index < data.length; index++)
            normalized[index] = (data[index] - mean) / variance;
        return normalized;
	}

	public static double variance(double[] data, double mean) {
		double numerator = 0;
		
		for (int index = 0; index < data.length; index++)
			numerator = numerator + ((data[index] - mean) * (data[index] - mean));
		return numerator / (double)(data.length - 1);
	}

	public static double standardDeviation(double[] data, double mean) {
		double var = variance(data, mean);
		return Math.sqrt(var);
	}

	public static double max(double[] data) {
		if (data.length == 0) {
			return (double)0.0;
		}

		double result = data[0];
		
		for (int index = 1; index < data.length; index++) {
			if (data[index] > result)
				result = data[index];
		}
		return result;
	}

	public static double min(double[] data) {
		if (data.length == 0) {
			return (double)0;
		}

		double result = data[0];
		
		for (int index = 1; index < data.length; index++) {
			if (data[index] < result)
				result = data[index];
		}
		return result;
	}
}
