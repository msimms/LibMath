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

global _NearestPowerOf2

section .text

; unsigned long NearestPowerOf2(unsigned long num)
_NearestPowerOf2:
	push rbp
	mov rbp, rsp

	; n = num > 0 ? num - 1 : 0
	xor rbx, rbx
	; if rcx == 0 then jump to doing the shifts, rcx is the first parameter (i.e. num)
	cmp rcx, $0
	je shifts
	; rbx = rcx - 1
	mov rbx, rcx
	sub rbx, $1

shifts:
	; n |= n >> 1
	mov rax, rbx
	shr rax, $1
	or rbx, rax

	; n |= n >> 2
	mov rax, rbx
	shr rax, $2
	or rbx, rax

	; n |= n >> 4
	mov rax, rbx
	shr rax, $4
	or rbx, rax

	; n |= n >> 8
	mov rax, rbx
	shr rax, $8
	or rbx, rax

	; n |= n >> 16
	mov rax, rbx
	shr rax, $16
	or rax, rbx

	; n++
	add rax, $1

	pop rbp
	ret
