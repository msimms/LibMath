
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

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * <h1>CsvReader</h1>
 * Class for reading comma separated files.
 */
public class CsvReader
{
    public static ArrayList<String[]> readAsStrings(String fileName) throws IOException {
        ArrayList<String[]> rows = new ArrayList<String[]>();
        BufferedReader br = null;

        try {
            String rowStr = "";
            br = new BufferedReader(new FileReader(fileName));
            while ((rowStr = br.readLine()) != null) {
                String[] row = rowStr.split(",");
                rows.add(row);
            }
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                }
            }
        }
        return rows;
    }

    public static ArrayList<double[]> readAsDoubles(String fileName) throws IOException {
        ArrayList<double[]> rows = new ArrayList<double[]>();
        BufferedReader br = null;

        try {
            String rowStr = "";
            br = new BufferedReader(new FileReader(fileName));
            while ((rowStr = br.readLine()) != null) {
                String[] row = rowStr.split(",");
                double[] numRow = new double[row.length];
                int numRowIndex = 0;
                for (String item:row) {
                    double numItem = Double.parseDouble(item);
                    numRow[numRowIndex++] = numItem;
                }
                rows.add(numRow);
            }
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                }
            }
        }
        return rows;
    }

    public static ArrayList<double[]> readAsDoublesColumnwise(String fileName) throws IOException {
        ArrayList<double[]> columns = new ArrayList<double[]>();
        ArrayList<double[]> rows = readAsDoubles(fileName);

        double[] tsList = new double[rows.size()];
        double[] xList = new double[rows.size()];
        double[] yList = new double[rows.size()];
        double[] zList = new double[rows.size()];

        for (int i = 0; i < rows.size(); ++i) {
            double[] row = rows.get(i);
            tsList[i] = row[0];
            xList[i] = row[1];
            yList[i] = row[2];
            zList[i] = row[3];
        }

        columns.add(tsList);
        columns.add(xList);
        columns.add(yList);
        columns.add(zList);
        return columns;
    }
}
