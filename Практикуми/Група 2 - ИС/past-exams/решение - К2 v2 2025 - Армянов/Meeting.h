#pragma once

#include "Event.h"
#include "Task.h"

class GuestList
{
public:
	GuestList();

	GuestList(const GuestList& other);
	GuestList(GuestList&& other) noexcept;

	GuestList& operator=(const GuestList& other);
	GuestList& operator= (GuestList&& other) noexcept;

	~GuestList() noexcept;

	bool isEmpty() const { return count == 0; }

	size_t getCount() const { return count; }
	char* operator[](size_t index);
	const char* operator[](size_t index) const;

	bool operator[](const char* name) const;
	GuestList& operator+= (const char* name);

private:
	void free();
	void copyList(char** list, size_t count);

private:
	char** guests;
	size_t count;
};

GuestList operator+(const GuestList& list, const char* name);

std::ostream& operator<<(std::ostream& out, const GuestList& list);
std::istream& operator>>(std::istream& in, GuestList& list);

class Meeting : public Event
{
	friend std::ostream& operator<<(std::ostream& out, const Meeting& meating);
	friend std::istream& operator>>(std::istream& in, Meeting& meating);

public:
	Meeting() = default;
	Meeting(
		const char* name,
		const char* description,
		unsigned length,
		bool repeating
	);

	Meeting& operator+=(const char* guest);

	bool operator[](const char* name) const;

	Task operator() (
		const char* name, 
		const char* description, 
		unsigned length, 
		bool repeating, 
		const Date& date) const;

	size_t getCountGuests() const { return guestList.getCount(); }

private:
	GuestList guestList;
};

