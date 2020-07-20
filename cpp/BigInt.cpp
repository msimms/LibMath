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

#include <iomanip>
#include <sstream>
#include <string>
#include <random>

#include "BigInt.h"

namespace LibMath
{
	BigInt::BigInt()
	{
		init(2048);
	}

	BigInt::BigInt(uint32_t bits)
	{
		init(bits);
	}

	BigInt::~BigInt()
	{
		free();
	}

	void BigInt::init(uint32_t bits)
	{
		m_numBits = bits;
		m_numWords = m_numBits / sizeof(m_numWords);
		if (m_numWords % sizeof(m_numWords) > 0)
			++m_numWords;
		m_data = new uint32_t[m_numWords];
		m_error = BIG_INT_NO_ERROR;
	}

	void BigInt::free()
	{
		if (m_data)
		{
			memset(m_data, 0, m_numWords * sizeof(uint32_t));
			delete[] m_data;
			m_data = NULL;
			m_error = BIG_INT_NO_ERROR;
		}
	}
	
	void BigInt::clear()
	{
		if (m_data)
		{
			memset(m_data, 0, m_numWords * sizeof(uint32_t));
			m_error = BIG_INT_NO_ERROR;
		}
	}

	void BigInt::set(uint32_t n)
	{
		clear();
		m_data[0] = n;
	}

	void BigInt::setMax()
	{
		for (size_t i = 0; i < m_numWords; ++i)
		{
			m_data[i] = (uint32_t)-1;
		}
	}

	void BigInt::setRand()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<unsigned long> dis(0, (uint32_t)-1);
		
		for (size_t i = 0; i < m_numWords; ++i)
		{
			m_data[i] = (uint32_t)dis(gen);
		}
	}

	uint32_t BigInt::addWords(uint32_t& a, uint32_t b)
	{
		uint32_t headroom = (uint32_t)-1 - b - 1;

		if (a <= headroom)
		{
			a += b;
			return 0;
		}

		a = (uint32_t)-1;
		return b - headroom;
	}

	uint32_t BigInt::subWords(uint32_t& a, uint32_t b)
	{
		if (b < a)
		{
			a -= b;
			return 0;
		}

		a = (uint32_t)((uint64_t)0x100000000 - (uint64_t)b);
		return 1;
	}

	void BigInt::add(const BigInt& n)
	{
		if (n.numBits() != m_numBits)
			return;

		uint32_t carry = 0;

		for (size_t i = 0; i < m_numWords; ++i)
		{
			carry += addWords(m_data[i], carry);
			carry += addWords(m_data[i], n.m_data[i]);
		}
		if (carry) // Overflow
		{
			m_error = BIG_INT_OVERFLOW;
		}
	}

	void BigInt::subtract(const BigInt& n)
	{
		if (n.numBits() != m_numBits)
			return;

		uint32_t borrow = 0;

		for (size_t i = 0; i < m_numWords; ++i)
		{
			if (borrow)
			{
				m_data[i] -= 1;
			}
			borrow = subWords(m_data[i], n.m_data[i]);
		}
		if (borrow) // Underflow
		{
			m_error = BIG_INT_UNDERFLOW;
		}
	}

	void BigInt::multiply(uint32_t n)
	{
		uint32_t carry = 0;

		for (size_t i = 0; i < m_numWords; ++i)
		{
			uint64_t temp = n * (uint64_t)m_data[i] + carry;
			m_data[i] = (uint32_t)temp;
			carry = temp >> 32;
		}
		if (carry) // Overflow
		{
			m_error = BIG_INT_OVERFLOW;
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
		std::ostringstream strStream;

		strStream << "0x";
		for (size_t i = m_numWords - 1; i > 0; --i)
		{
			strStream << std::setfill('0') << std::setw(8) << std::hex << m_data[i];
		}
		strStream << std::setfill('0') << std::setw(8) << std::hex << m_data[0];
		return strStream.str();
	}
}
