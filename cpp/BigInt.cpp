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

#include <string>
#include <random>

#include "BigInt.h"

namespace LibMath
{
	BigInt::BigInt()
	{
		init(2048);
	}

	BigInt::BigInt(uint64_t bits)
	{
		init(bits);
	}

	BigInt::~BigInt()
	{
		clear();
	}

	void BigInt::init(uint64_t bits)
	{
		m_numBits = bits;
		m_numWords = m_numBits / sizeof(m_numWords);
		if (m_numWords % sizeof(m_numWords) > 0)
			++m_numWords;
	}

	void BigInt::clear()
	{
		if (m_data)
		{
			memset(m_data, 0, m_numWords * sizeof(uint64_t));
			m_data = NULL;
		}
	}

	void BigInt::rand()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<unsigned long long> dis(0, (unsigned long long)-1);
		
		for (size_t i = 0; i < m_numWords; ++i)
		{
			m_data[i] = dis(gen);
		}
	}

	uint64_t BigInt::addWords(uint64_t& a, uint64_t b)
	{
		uint64_t headroom = (uint64_t)-1 - b - 1;

		if (a <= headroom)
		{
			a += b;
			return 0;
		}

		a = (uint64_t)-1;
		return b - headroom;
	}

	void BigInt::add(const BigInt& n)
	{
		if (n.numBits() != m_numBits)
			return;

		uint64_t carry = 0;

		for (size_t i = 0; i < m_numWords; ++i)
		{
			carry += addWords(m_data[i], carry);
			carry += addWords(m_data[i], n.m_data[i]);
		}
	}

	void BigInt::subtract(const BigInt& n)
	{
		for (size_t i = 0; i < m_numWords; ++i)
		{
		}
	}

	void BigInt::multiply(const BigInt& n)
	{
		for (size_t i = 0; i < m_numWords; ++i)
		{
		}
	}

	void BigInt::divide(const BigInt& n)
	{
		for (size_t i = 0; i < m_numWords; ++i)
		{
		}
	}

	bool BigInt::compare(const BigInt& n) const
	{
		if (n.numBits() != m_numBits)
			return false;

		for (size_t i = 0; i < m_numWords; ++i)
		{
			if (m_data[i] != n.m_data[i])
				return false;
		}
		return true;
	}

	bool BigInt::isPrime() const
	{
		return false;
	}

	std::string BigInt::toString() const
	{
		return "";
	}
}
