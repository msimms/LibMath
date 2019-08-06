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
 * <h1>GraphPoint</h1>
 * Represents a point on a graph where the x value is an index and the y value is actual data.
 */
public class GraphPoint
{
    public long x;
    public double y;

    /**
     * Constructor.
     * 
     * @param newX
     *             x value of the new point.
     * @param newY
     *             y value of the new point.
     * @param rhs
     *             Point to be copied.
     */
    GraphPoint() {
        x = 0;
        y = (double)0.0;
    }
    GraphPoint(long newX, double newY) {
        x = newX;
        y = newY;
    }
    GraphPoint(GraphPoint rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    /**
     * Sets all the values associated with the point to zero.
     */
    public void clear() {
        x = 0;
        y = (double)0.0;
    }
};
