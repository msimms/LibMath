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

#include <stdio.h>

#include "SquareMatrix.h"

int main(int argc, const char * argv[])
{
	SquareMatrixPtr m = squareMatrixCreate(5);
	squareMatrixIdentity(m);
	printf("Identity matrix:\n");
	squareMatrixPrint(m);
	squareMatrixDestroy(m);

	m = squareMatrixCreate(5);
	squareMatrixZero(m);
	printf("Zero matrix:\n");
	squareMatrixPrint(m);
	squareMatrixOnes(m);
	printf("Ones matrix:\n");
	squareMatrixPrint(m);
	squareMatrixMultiplyByScalar(m, 2.0);
	printf("Ones matrix multiplied by 2.0:\n");
	squareMatrixPrint(m);
	squareMatrixDestroy(m);
	
	return 0;
}
