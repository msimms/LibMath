; by Michael J. Simms
; Copyright (c) 2018 Michael J. Simms

; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be included in all
; copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.

global _VectorMultiply
global _VectorSubtract
global _VectorDot
global _VectorLength
global _VectorNormalize
global _VectorCross

section .text

; double vectorMultiply(const double* A, const double* B, size_t vecLen)
_VectorMultiply:
	push rbp
	mov rbp, rsp
	mov rax, $0
	ret

; void vectorSubtract(const double* A, const double* B, double* C, size_t vecLen)
_VectorSubtract:
	push rbp
	mov rbp, rsp
	ret

; double vectorDot(const double* A, const double* B, size_t vecLen)
_VectorDot:
	push rbp
	mov rbp, rsp
	mov rax, $0
	ret

; double vectorLength(const double* A, size_t vecLen)
_VectorLength:
	push rbp
	mov rbp, rsp
	mov rax, $0
	ret

; void vectorNormalize(double* A, size_t vecLen)
_VectorNormalize:
	push rbp
	mov rbp, rsp
	ret

; void vectorCross(const double* A, const double* B, double* C, size_t vecLen)
_VectorCross:
	push rbp
	mov rbp, rsp
	ret
