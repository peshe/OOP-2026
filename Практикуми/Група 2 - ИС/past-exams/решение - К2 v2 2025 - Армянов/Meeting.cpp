#include "Meeting.h"

#include "Utils.h"

#include <iostream>
#include <stdexcept>

GuestList::GuestList()
	: guests(nullptr), count(0)
{
}

GuestList::GuestList(const GuestList& other)
	: guests(nullptr), count(other.count)
{
	if (!other.guests) return;

	this->guests = new char* [other.count] {};

	try
	{
		for (size_t i = 0; i < count; ++i)
		{
			this->guests[i] = copy(other.guests[i]);
		}
	}
	catch (std::exception&)
	{
		free();
		throw;
	}
}

GuestList::GuestList(GuestList&& other) noexcept
	: guests(nullptr), count(other.count)
{
	std::swap(this->guests, other.guests);
	other.count = 0;
}

GuestList& GuestList::operator=(const GuestList& other)
{
	if (this != &other)
	{
		free();
		copyList(other.guests, other.count);
	}

	return *this;
}

GuestList& GuestList::operator=(GuestList&& other) noexcept
{
	if (this != &other)
	{
		std::swap(this->guests, other.guests);
		std::swap(this->count, other.count);
	}

	return *this;
}

GuestList::~GuestList() noexcept
{
	free();
}

char* GuestList::operator[](size_t index)
{
	if (index >= count)
		throw std::out_of_range("Index out of range!");

	return this->guests[index];
}

const char* GuestList::operator[](size_t index) const
{
	if (index >= count)
		throw std::out_of_range("Index out of range!");

	return this->guests[index];
}

bool GuestList::operator[](const char* name) const
{
	for (size_t i = 0; i < count; ++i)
	{
		if (strcmp(this->guests[i], name) == 0)
			return true;
	}

	return false;
}

GuestList& GuestList::operator+=(const char* name)
{
	char** temp = new char* [count + 1] {};
	for (size_t i = 0; i < count; ++i)
	{
		temp[i] = this->guests[i];
	}

	try
	{
		char* newGuest = copy(name);
		temp[count] = newGuest;
		++count;

		delete[] this->guests;
		this->guests = temp;
	}
	catch (...)
	{
		delete[] temp;
		throw;
	}

	return *this;
}

void GuestList::free()
{
	for (size_t j = 0; j < count; ++j)
	{
		delete this->guests[j];
	}

	delete[] this->guests;
	this->guests = nullptr;
}

void GuestList::copyList(char** list, size_t count)
{
	if (!list)
		return;

	this->count = count;
	this->guests = new char* [count] {};

	try
	{
		for (size_t i = 0; i < count; ++i)
		{
			this->guests[i] = copy(list[i]);
		}
	}
	catch (std::exception&)
	{
		free();
		throw;
	}
}

GuestList operator+(const GuestList& list, const char* name)
{
	GuestList result = list;
	result += name;
	return result;
}

std::ostream& operator<<(std::ostream& out, const GuestList& list)
{
	size_t count = list.getCount();

	out << count << '\n';
	for (size_t i = 0; i < count; ++i)
	{
		out << list[i] << '\n';
	}

	return out;
}

std::istream& operator>>(std::istream& in, GuestList& list)
{
	size_t count = 0;
	in >> count;

	skipWhiteSpaces(in);

	GuestList newList;

	size_t i = 0;
	while (in && i < count)
	{
		char* guest = readString(in, '\n');
		if (guest)
		{
			try
			{
				newList += guest;
				delete[] guest;
			}
			catch (...)
			{
				delete[] guest;
				throw;
			}
		}

		++i;
	}

	list = std::move(newList);
	return in;
}

Meeting::Meeting(const char* name, const char* description, unsigned length, bool repeating)
    : Event(name, description, length, repeating)
{ }

Meeting& Meeting::operator+=(const char* guest)
{
    this->guestList += guest;
    return *this;
}

bool Meeting::operator[](const char* name) const
{
    return this->guestList[name];
}

Task Meeting::operator()(
    const char* name, 
    const char* description, 
    unsigned length, 
    bool repeating, 
    const Date& date) const
{
    return Task(name, description, length, repeating, date);
}

std::ostream& operator<<(std::ostream& out, const Meeting& meating)
{
    out << (Event&)meating;
    out << meating.guestList << '\n';

    return out;
}

std::istream& operator>>(std::istream& in, Meeting& meating)
{
    Event event;
    in >> event;

    GuestList guestlist;
    in >> guestlist;

    if (in)
    {
        (Event&) meating = std::move(event);
        meating.guestList = std::move(guestlist);
    }

    return in;
}
