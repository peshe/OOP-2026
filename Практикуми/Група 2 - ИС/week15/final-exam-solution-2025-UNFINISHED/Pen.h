#pragma once

#include "WI.h"

class Pen : public WI
{
public:
	Pen() = default;

	Pen(Color color, const char* name, const char* descr, bool written)
		:WI(color, name, descr, written)
	{ }

	void setDescr(const char* descr) override
	{
		WI::setDescr(descr);
	}

	void writeOut()
	{
		written = true;
	}

	void store(std::ostream& os) override
	{
		WI::store(os);
	}
	void load(std::istream& is) override
	{
		WI::load(is);
	}
	WI* clone() const override
	{
		return new Pen(*this);
	}

	void print() const override
	{
		WI::print();
	}

	void swap(Pen& other)
	{
		WI::swap(other);
	}

	Type getType() const override
	{
		return Type::Pen;
	}
};

int main()
{

}