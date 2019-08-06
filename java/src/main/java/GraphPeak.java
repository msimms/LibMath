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

/**
 * <h1>GraphPeak</h1>
 * Represents a peak that was found with the peak finding algorithm.
 * A peak consists of a left trough, right trough, and peak (obvously).
 */
public class GraphPeak
{
    public GraphPoint leftTrough;
    public GraphPoint peak;
    public GraphPoint rightTrough;
    public double area;
    
    /**
     * Constructor.
     */
    GraphPeak() {
        this.leftTrough = new GraphPoint();
        this.peak = new GraphPoint();
        this.rightTrough = new GraphPoint();
        this.area = (double)0.0;
    }

    /**
     * Copy constructor.
     * 
     * @param rhs
     *             Peak to be copied.
     */
    GraphPeak(GraphPeak rhs) {
        this.leftTrough = rhs.leftTrough;
        this.peak = rhs.peak;
        this.rightTrough = rhs.rightTrough;
        this.area = rhs.area;
    }

    /**
     * Copy constructor.
     * 
     * @param rhs
     *             Peak to be copied.
     */
    public void copy(GraphPeak rhs) {
        this.leftTrough = rhs.leftTrough;
        this.peak = rhs.peak;
        this.rightTrough = rhs.rightTrough;
        this.area = rhs.area;
    }

    /**
     * Comparitor. Peaks are the same if they have the same troughts and peak.
     * 
     * @param rhs
     *             Peak to be compared.
     */
    public boolean compare(GraphPeak rhs) {
        return (this.leftTrough == rhs.leftTrough) && (this.peak == rhs.peak) && (this.rightTrough == rhs.rightTrough);
    }

    /**
     * Comparison by area.
     * 
     * @param rhs
     *             Peak to be compared.
     */
    public boolean lessThan(GraphPeak str) { return (area < str.area); }
    public boolean greaterThan(GraphPeak str) { return (area > str.area); }
    
    /**
     * Sets all the values associated with the peak to zero.
     */
    public void clear() {
        this.leftTrough.clear();
        this.peak.clear();
        this.rightTrough.clear();
        this.area = (double)0.0;
    }
};
