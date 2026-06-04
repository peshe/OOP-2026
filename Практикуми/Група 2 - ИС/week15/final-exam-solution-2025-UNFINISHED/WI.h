#pragma once
#include <stdexcept>
#include <cstring>
#include <utility>
#include <fstream>
#include <iostream>
#pragma warning (disable : 4996)

enum class Color
{
	RED,
	Blue,
	Green,
	Black
};

const char* colors[10] = {
	"RED",
	"Blue",
	"Green",
	"Black"
};

enum class Type
{
	Pen,
	AutoPencil,
	MultiPen,
	PenSet
};

class WI
{
public:
	WI()
		:WI(Color::RED, "no name", "", false)
	{}
	WI(Color color, const char* name, const char* descr, bool isWritten)
		:color(color), written(isWritten)
	{
		setName(name);
		try
		{
			setDescr(descr);
		}
		catch (...)
		{
			delete[] name;
			throw;
		}
	}

	WI(const WI& other)
		:WI(other.color, other.name, other.descr, other.written)
	{ }

	WI& operator=(const WI& other)
	{
		if (&other != this)
		{
			char* temp1;
			char* temp2;
			try
			{
				temp1 = strcpy(new char[strlen(other.name) + 1], other.name);
				temp2 = strcpy(new char[strlen(other.descr) + 1], other.descr);
			}
			catch (const std::exception&)
			{
				delete[] temp1;
				delete[] temp2;
				throw;
			}
			delete[] name;
			delete[] descr;
			name = temp1;
			descr = temp2;
			color = other.color;
			written = other.written;

		}
		return *this;
	}

	virtual ~WI()
	{
		delete[] name;
		delete[] descr;
	}

	virtual Type getType() const = 0;

	Color getColor() const { return color; }
	const char* getName() const { return name; }
	const char* getDescr() const { return descr; }
	virtual bool getWritten() const { return written; }

	virtual void print() const = 0;
	virtual void store(std::ostream& os) = 0;
	virtual void load(std::istream& os) = 0;
	virtual WI* clone() const = 0;

protected:
	Color color;
	char* name = nullptr;
	char* descr = nullptr;
	bool written;

	void swap(WI& other)
	{
		std::swap(color, other.color);
		std::swap(name, other.name);
		std::swap(descr, other.descr);
		std::swap(written, other.written);
	}

	virtual void setColor(Color color)
	{
		this->color = color;
	}
	virtual void setWritten(bool written)
	{
		this->written = written;
	}

	virtual void setName(const char* name)
	{
		if (!name || strlen(name) == 0) throw std::runtime_error("nullptr");
		char* temp = strcpy(new char[strlen(name) + 1], name);
		delete[] this->name;
		this->name = temp;
	}

	virtual void setDescr(const char* descr)
	{
		if (!descr) throw std::runtime_error("nullptr");
		char* temp = strcpy(new char[strlen(descr) + 1], descr);
		delete[] this->descr;
		this->descr = temp;
	}
};

bool operator==(const WI& l, const WI& r)
{
	return l.getColor() == r.getColor();
}

bool operator!=(const WI& l, const WI& r)
{
	return !(l == r);
}

void WI::print() const
{
	std::cout << name << ' ' << descr << ' ' << written << colors[(int)color] << '\n';
}

void WI::store(std::ostream& os)
{
	unsigned namesize = strlen(name);
	unsigned descrsize = strlen(descr);
	os.write((const char*)&written, sizeof(color));
	os.write((const char*)&color, sizeof(color));
	os.write((const char*)&namesize, sizeof(namesize));
	os.write((const char*)&descrsize, sizeof(descrsize));
	os.write(name, namesize);
	os.write(descr, descrsize);

}
void WI::load(std::istream& os)
{

}
