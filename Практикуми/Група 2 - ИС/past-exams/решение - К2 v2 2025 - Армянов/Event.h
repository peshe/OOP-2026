#pragma once

#include <iostream>

class Event
{
public:
	Event(
		const char* name = "Name", 
		const char* description = "Description", 
		unsigned length = 0, 
		bool repeating = false
	);

	Event(const Event& other);
	Event(Event&& other) noexcept;

	Event& operator=(const Event& other);
	Event& operator=(Event&& other) noexcept;

	~Event() noexcept;

	const char* getName() const { return this->name; }
	const char* getDescription() const { return this->description; }
	unsigned getLength() const { return length; }
	bool isRepeating() const { return repeating; }

private:
	char* name;
	char* description;
	unsigned length;
	bool repeating;
};

bool operator==(const Event& left, const Event& right);
bool operator!=(const Event& left, const Event& right);

std::ostream& operator<<(std::ostream& out, const Event& event);
std::istream& operator>>(std::istream& out, Event& event);