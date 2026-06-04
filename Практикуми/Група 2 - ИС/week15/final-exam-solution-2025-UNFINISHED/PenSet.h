#pragma once

#include "WI.h"
#include "Pen.h"
#include "MultiPen.h"
#include "AutoPencil.h"

class PenSet : public WI
{
public:
	PenSet() = default;
	PenSet(Color color, const char* name, const char* descr, bool written)
		:WI(color, name, descr, written)
	{
		wis = new WI * [cap] {};
		size = 0;
	}

	PenSet& operator-=(unsigned index)
	{
		if (index >= size) throw;
		delete[] wis[index];
		for (int i = index; i < size - 1; i++)
		{
			wis[i] = wis[i + 1];
		}
		size--;
		return *this;
	}

	PenSet& operator+=(WI* pen)
	{
		if (size == cap) resize();
		wis[size] = pen->clone();
		size++;
	}

	Type getType() const override
	{
		return Type::PenSet;
	}

	void store(std::ostream& os) override
	{
		os.write((const char*)size, sizeof(size));
		os.write((const char*)cap, sizeof(cap));
		for (int i = 0; i < size; i++)
		{
			Type t = wis[i]->getType();
			os.write((const char*)t, sizeof(Type));
			wis[i]->store(os);
		}
	}
	void load(std::istream& is) override
	{
		unsigned nsize;
		unsigned ncap;
		WI** nwis;
		is.read((char*)nsize, sizeof(nsize));
		is.read((char*)ncap, sizeof(ncap));
		nwis = new WI * [ncap] {};
		for (int i = 0; i < nsize; i++)
		{
			Type t;
			WI* w;
			is.read((char*)t, sizeof(t));
			switch (t)
			{
			case Type::Pen:
				w = new Pen;
				break;
			case Type::AutoPencil:
				w = new AutoPencil;
				break;
			case Type::MultiPen:
				w = new MultiPen;
				break;
			case Type::PenSet:
				w = new PenSet;
				break;
			default:
				break;
			}
			w->load(is);
			nwis[i] = w;
		}
	}
	WI* clone() const override
	{
		return new PenSet(*this);
	}


	void print() const override
	{
		WI::print();
		for (int i = 0; i < size; i++)
		{
			wis[i]->print();
		}
	}

private:
	WI** wis;
	unsigned size;
	unsigned cap = 4;

	void resize()
	{
		WI** temp = new WI * [cap * 2];
		for (int i = 0; i < size; i++)
		{
			temp[i] = wis[i]->clone();
		}
		for (int i = 0; i < size; i++)
		{
			delete wis[i];
		}
		delete[] wis;
		cap *= 2;
		wis = temp;
	}
};