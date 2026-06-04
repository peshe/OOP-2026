#pragma once

#include "WI.h"

class AutoPencil : public WI
{
public:
	AutoPencil()
		:AutoPencil(1, 2, 2)
	{ }

	AutoPencil(unsigned minL, unsigned maxL, unsigned currL)
		:minLen(minL), maxLen(maxL)
	{
		setCurrLen(currL);
	}

	void setCurrLen(unsigned currLen)
	{
		if (currLen > maxLen)
		{
			currLen = maxLen;
		}
		else if (currLen < minLen)
		{
			written = true;
			//currLen = 0;
		}
		this->currLen = currLen;
	}

	AutoPencil& operator-=(double num)
	{
		if (currLen < num) return;
		if (num < 0) return;
		setCurrLen(currLen - num);
		return *this;
	}

	AutoPencil operator++(int)
	{
		AutoPencil temp(*this);
		++(*this);
		return temp;
	}

	AutoPencil& operator++()
	{
		currLen = maxLen;
		written = false;
		return *this;
	}

	AutoPencil operator--(int)
	{
		AutoPencil temp(*this);
		--(*this);
		return temp;
	}

	AutoPencil& operator--()
	{
		currLen = 0;
		return *this;
	}

	void setColor(Color color) override
	{
		if (written) this->color = color;
	}
	void store(std::ostream& os) override
	{
		WI::store(os);
		//!!!!

	}
	void load(std::istream& is) override
	{
		//WI::load(is);
		//!!!
		AutoPencil copy(*this);
		copy.WI::load(is);
		//!!!
		*this = copy;
	}
	WI* clone() const override
	{
		return new AutoPencil(*this);
	}

	void print() const override
	{
		WI::print();
		std::cout << minLen << maxLen << currLen;
	}

	Type getType() const override
	{
		return Type::AutoPencil;
	}

private:
	const unsigned minLen;
	const unsigned maxLen;
	unsigned currLen;
};


AutoPencil operator-(const AutoPencil& ap, int x)
{
	AutoPencil temp(ap);
	return temp -= x;
}