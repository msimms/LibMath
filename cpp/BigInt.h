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

#pragma once

#ifndef _BIGINT_
#define _BIGINT_

#include <stdint.h>
#include <string>

namespace LibMath
{
	typedef enum BigIntError
	{
		BIG_INT_NO_ERROR = 0,
		BIG_INT_OVERFLOW,
		BIG_INT_UNDERFLOW
	} BigIntError;

	class BigInt
	{
	public:
		BigInt();
		BigInt(uint32_t bits);
		virtual ~BigInt();

		bool operator==(const BigInt& rhs) const { return compare(rhs); }
		BigInt& operator+=(const BigInt& rhs) { add(rhs); return *this; }
		BigInt& operator-=(const BigInt& lhs) { subtract(lhs); return *this; }
		BigInt& operator*=(const BigInt& lhs) { multiply(lhs); return *this; }
		BigInt& operator/=(const BigInt& lhs) { divide(lhs); return *this; }

		uint32_t numBits() const { return m_numBits; }

		void clear();
		void set(uint32_t n);
		void setMax();
		void setRand();
		void add(const BigInt& n);
		void subtract(const BigInt& n);
		void multiply(uint32_t n);
		void multiply(const BigInt& n);
		void divide(const BigInt& n);

		bool compare(const BigInt& n) const;
		bool isPrime() const;

		std::string toString() const;

	private:
		uint32_t m_numBits;
		uint32_t m_numWords;
		uint32_t* m_data; // m_data[0] is least significant, m_data[m_numWords - 1] is most significant
		BigIntError m_error;

		void init(uint32_t bits);
		void free();

		uint32_t addWords(uint32_t& a, uint32_t b);
		uint32_t subWords(uint32_t& a, uint32_t b);
	};
}

#endif
