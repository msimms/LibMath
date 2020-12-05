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
import java.io.*;

public class LibMathTests
{
    public static void statisticsTests() {
        long v_int[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        double v_int_avg = Statistics.averageLong(v_int);
        System.out.println("Average: " + v_int_avg);
        double v_flt[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
        double v_flt_avg = Statistics.averageDouble(v_flt);
        System.out.println("Average: " + v_flt_avg);
        double variance = Statistics.variance(v_flt, v_flt_avg);
        System.out.println("Variance: " + variance);
    }
    
    public static void peakFindingTests(String csvFileName) {
        if (csvFileName.length() > 0) {
            try {
                ArrayList<double[]> csvData = CsvReader.readAsDoublesColumnwise(csvFileName);
                Iterator<double[]> csvIter = csvData.iterator();
                if (csvIter.hasNext()) {
                    csvIter.next(); // Skip over the timestamp column
                    int axisCount = 0;
                    while (csvIter.hasNext()) {
                        double[] columnData = csvIter.next();
                        System.out.println("Axis " + (++axisCount) + ": ");

			            int peakCount = 0;
			            ArrayList<GraphPeak> peaks = Peaks.findPeaks(columnData, (double)1.5);
                        Iterator<GraphPeak> peakIter = peaks.iterator();
                        while (peakIter.hasNext()) {
                            GraphPeak peak = peakIter.next();
				            System.out.println("Peak " + (++peakCount) + ": {" + peak.leftTrough.x + ", " + peak.peak.x + ", " + peak.rightTrough.x + ", " + peak.area + "}");
                        }
                    }
                }
            }
            catch (IOException e) {
            }
        }
    }

    /**
     * Entry point.
     */
    public static void main(String[] args) {
        String csvFileName = new String();

    	for (int i = 0; i < args.length; ++i) {
            if (args[i].equals("--csv") && (i + 1 < args.length)) {
                csvFileName = args[++i];
            }
        }

        System.out.println("Statistics Tests:");
        System.out.println("-----------------");
        statisticsTests();

        System.out.println("\nPeak Finding Tests:");
        System.out.println("-------------------");
        peakFindingTests(csvFileName);
    }
}
