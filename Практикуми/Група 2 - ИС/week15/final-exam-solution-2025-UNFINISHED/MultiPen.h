#pragma once

#include "WI.h"
#include "Pen.h"

class MultiPen : public WI
{
public:
	MultiPen() = default;

	MultiPen(Color color, const char* name, const char* descr, bool written)
		:WI(color, name, descr, written) {
		size = 0;
		on = -1;
	}

	MultiPen& operator=(const MultiPen& other)
	{
		if (this != &other)
		{
			MultiPen copy(other);
			for (int i = 0; i < MAX_PENS; i++)
			{
				pens[i].swap(copy.pens[i]);
			}
			size = other.size;
			on = other.on;
		}
		return *this;
	}

	bool getWritten() const override
	{
		for (int i = 0; i < size; i++)
		{
			if (!pens[i].getWritten()) {
				return false;
			}
		}
		return true;
	}

	void addPen(const Pen& pen)
	{
		for (int i = 0; i < size; i++)
		{
			if (pens[i].getColor() == pen.getColor()) throw;
		}
		if (size == MAX_PENS) throw std::runtime_error("sasa");
		pens[size] = pen;
		size++;
	}
	void removePen(Color color)
	{
		for (int i = 0; i < size; i++)
		{
			if (pens[i].getColor() == color) {

				pens[i].swap(pens[size - 1]);
				size--;
			}
		}
		if (size == 0) throw std::runtime_error("e,pty");

	}

	bool operator()(Color color)
	{
		for (int i = 0; i < size; i++)
		{
			if (pens[i].getColor() == color && !pens[i].getWritten()) {
				on = i;
				return true;
			}
		}
		return false;
	}

	Color getColor() const
	{
		if (on != -1) return pens[on].getColor();
		return color;
	}

	void store(std::ostream& os) override
	{

	}
	void load(std::istream& os) override
	{

	}
	WI* clone() const override
	{
		return new MultiPen(*this);
	}

	Type getType() const override
	{
		return Type::MultiPen;
	}

	void print() const override
	{
		WI::print();
		for (int i = 0; i < size; i++)
		{
			pens[i].print();
		}
	}

	void swap(Pen& other)
	{
		WI::swap(other);
	}

private:
	static const unsigned MAX_PENS = 10;

	Pen pens[MAX_PENS];
	unsigned size;
	short on;
};