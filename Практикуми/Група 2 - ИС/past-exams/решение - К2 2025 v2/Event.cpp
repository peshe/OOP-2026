#define _CRT_SECURE_NO_WARNINGS
#include "Event.h"
#include "Utils.h"

#include <cstring>
#include <exception>
#include <stdexcept>

Event::Event(const char* name, const char* description, unsigned length, bool repeating)
    : name(nullptr), description(nullptr), length(length), repeating(repeating)
{
    try
    {
        this->name = copy(name);
        this->description = copy(description);
    }
    catch (std::exception& )
    {
        delete[] this->name;
        delete[] this->description;
        
        throw;
    }
}

Event::Event(const Event& other)
    : Event(other.name, other.description, other.length, other.repeating)
{ }

Event::Event(Event && other) noexcept
    : name(nullptr), description(nullptr), length(other.length), repeating(other.repeating)
{
    std::swap(name, other.name);
    std::swap(description, other.description);
}

Event& Event::operator=(const Event & other)
{
    if (this != &other)
    {
        Event copy = other;
        *this = std::move(copy);
    }

    return *this;
}

Event& Event::operator=(Event&& other) noexcept
{
    if (this != &other)
    {
        std::swap(this->name, other.name);
        std::swap(this->description, other.description);
        this->length = other.length;
        this->repeating = other.repeating;
    }

    return *this;
}

Event::~Event() noexcept
{
    delete[] this->name;
    delete[] this->description;
}

bool operator==(const Event& left, const Event& right)
{
    return
        strcmp(left.getName(), right.getName()) == 0 &&
        strcmp(left.getDescription(), right.getDescription()) == 0 &&
        left.getLength() == right.getLength() &&
        left.isRepeating() == right.isRepeating();
}

bool operator!=(const Event& left, const Event& right)
{
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Event& event)
{
    out << event.getName() << '\n'
        << event.getLength() << '\t' << event.isRepeating() << '\n'
        << event.getDescription() << std::endl;

    return out;
}

std::istream& operator>>(std::istream& in, Event& event)
{
    char* name = readString(in, '\n');
    
    unsigned length = 0;
    in >> length;

    int repeating = 0;
    in >> repeating;

    skipWhiteSpaces(in);

    char* description = readString(in, '\n');

    if (in)
    {
        try
        {
            Event temp(name, description, length, repeating);
            event = std::move(temp);
        }
        catch (...)
        {
            in.setstate(std::ios_base::failbit);
        }
    }

    delete[] name;
    delete[] description;

    return in;
}
