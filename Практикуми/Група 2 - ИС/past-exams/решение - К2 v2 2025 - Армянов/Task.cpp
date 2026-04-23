#include "Task.h"

Task::Task(const char* name, const char* description, unsigned length, bool repeating, const Date& date)
	: Event(name, description, length, repeating), date(date)
{
}

void Task::setDate(const Date& date)
{
	this->date = date;
}

bool operator<(const Date& left, const Date& right)
{
	if (left.month < right.month)
		return true;

	if (left.month > right.month)
		return false;

	return left.day < right.day;
}

bool operator<=(const Date& left, const Date& right)
{
	return !(left > right);
}

bool operator>(const Date& left, const Date& right)
{
	return right < left;
}

bool operator>=(const Date& left, const Date& right)
{
	return !(left < right);
}

bool operator==(const Date& left, const Date& right)
{
	return left.month == right.month && left.day == right.day;
}

bool operator!=(const Date& left, const Date& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.day << '.' << date.month;
	return out;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	unsigned day, month;
	in >> day;
	
	char c;
	in.get(c);
	if (in && c != '.')
	{
		in.setstate(std::ios_base::failbit);
		return in;
	}

	in >> month;

	if (in)
	{
		date.day = day;
		date.month = month;
	}

	return in;
}

bool operator>(const Task& left, const Task& right)
{
	if(left.getDate() < right.getDate())
		return true;

	if (left.getDate() > right.getDate())
		return false;

	return left.getLength() > right.getLength();
}

bool operator>=(const Task& left, const Task& right)
{
	if (left.getDate() <= right.getDate())
		return true;

	return false;
}

bool operator<(const Task& left, const Task& right)
{
	// right > left
	return !(left >= right);
}

bool operator<=(const Task& left, const Task& right)
{
	return !(left > right);
}

std::ostream& operator<<(std::ostream& out, const Task& task)
{
	out << (Event&)task;
	out << task.getDate() << std::endl;

	return out;
}

std::istream& operator>>(std::istream& in, Task& task)
{	
	Event event;
	in >> event;

	Date date;
	in >> date;

	if (in)
	{
		(Event&)task = std::move(event);
		task.setDate(date);
	}

	return in;
}