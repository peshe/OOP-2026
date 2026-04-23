#include "Calendar.h"

Calendar::Calendar(unsigned month)
	: month(month)
{ }

Calendar::Calendar(const Calendar& other)
	: month(other.month)
	, events(nullptr), ce(other.ce)
	, tasks(nullptr), ct(other.ct)
	, meetings(nullptr), cm(other.cm)
{
	try
	{
		this->events = new EventForDate[ce]{};
		for (size_t i = 0; i < ce; ++i)
		{
			this->events[i] = other.events[i];
		}
		
		this->tasks = new TaskForDate[ct]{};
		for (size_t i = 0; i < ct; ++i)
		{
			this->tasks[i] = other.tasks[i];
		}

		this->meetings = new MeetingForDate[cm]{};
		for (size_t i = 0; i < cm; ++i)
		{
			this->meetings[i] = other.meetings[i];
		}

		for (size_t i = 0; i < COUNT_HOURS_IN_MONTH; ++i)
		{
			hours[i] = other.hours[i];
		}
	}
	catch (...)
	{
		free();
		throw;
	}
}

Calendar::~Calendar()
{
	free();
}

Calendar& Calendar::operator+=(const Task& task)
{
	if (task.getDate().month < month)
		return *this;

	unsigned day = 1, hour = 1;
	if (!findFirstFreeHour(day, hour))
		return *this;

	if (day >= task.getDate().day)
		return *this;

	TaskForDate* temp = new TaskForDate[ct + 1]{ };
	for (size_t i = 0; i < ct; ++i)
	{
		temp[i] = this->tasks[i];
	}
	
	TaskForDate newTask{ task, day, hour };
	temp[ct] = std::move(newTask);
	++ct;
	
	hours[day * 24 + hour] = true;

	delete[] this->tasks;
	this->tasks = temp;

	return *this;
}

Calendar& Calendar::operator+=(const Event& event)
{
	unsigned day = 1, hour = 1; 
	if (!findFirstFreeHour(day, hour))
		return *this;

	EventForDate* temp = new EventForDate[ce + 1]{ };
	for (size_t i = 0; i < ce; ++i)
	{
		temp[i] = this->events[i];
	}
	
	EventForDate newEvent{ event, day, hour };
	temp[ce] = std::move(newEvent);
	++ce;

	hours[day * 24 + hour] = true;

	delete[] this->events;
	this->events = temp;

	return *this;
}

Calendar& Calendar::operator+=(const Meeting& meating)
{
	unsigned day = 1, hour = 1;
	if (!findFirstFreeHour(day, hour))
		return *this;

	MeetingForDate* temp = new MeetingForDate[cm + 1]{ };
	for (size_t i = 0; i < cm; ++i)
	{
		temp[i] = this->meetings[i];
	}

	MeetingForDate newMeeting{ meating, day, hour };
	temp[cm] = std::move(newMeeting);
	++cm;

	hours[day * 24 + hour] = true;

	delete[] this->meetings;
	this->meetings = temp;

	return *this;
}

Calendar& Calendar::operator-=(const char* name)
{
	for (size_t i = 0; i < ce; ++i)
	{
		if (strcmp(events[i].event.getName(), name) == 0)
		{
			// shift left
			for (size_t j = i; j < ce; ++j)
			{
				events[j - 1] = events[j];
			}

			--ce;

			hours[24 * events[i].day + events[i].hour] = false;
		}
	}

	for (size_t i = 0; i < ct; ++i)
	{
		if (strcmp(tasks[i].task.getName(), name) == 0)
		{
			// shift left
			for (size_t j = i; j < ct; ++j)
			{
				tasks[j - 1] = tasks[j];
			}

			--ce;

			hours[24 * events[i].day + events[i].hour] = false;
		}
	}

	return *this;
}

Task* Calendar::operator[](const char* task)
{
	for(size_t i = 0; i < ct; ++i)
	{
		if (strcmp(this->tasks[i].task.getName(), task) == 0)
			return &this->tasks[i].task;
	}

	return nullptr;
}

const Task* Calendar::operator[](const char* task) const
{
	for (size_t i = 0; i < ct; ++i)
	{
		if (strcmp(this->tasks[i].task.getName(), task) == 0)
			return &this->tasks[i].task;
	}

	return nullptr;
}

void Calendar::free()
{
	delete[] this->events;
	this->events = nullptr;

	delete[] this->tasks;
	this->tasks = nullptr;

	delete[] this->meetings;
	this->meetings = nullptr;
}

bool Calendar::findFirstFreeHour(unsigned int& day, unsigned int& hour) const
{
	for (size_t i = 0; i < COUNT_HOURS_IN_MONTH; ++i)
	{
		if (!hours[i])
		{
			day = (unsigned) i / 24;
			hour = (unsigned) i % 24;

			return true;
		}
	}

	return false;
}

Calendar& Calendar::operator++()
{
	Calendar result(month + 1);
	for (size_t i = 0; i < ct; ++i)
	{
		if (tasks[i].task.getDate().month > month || tasks[i].task.isRepeating())
		{
			result += tasks[i].task;
		}
	}

	for (size_t i = 0; i < ce; ++i)
	{
		if (events[i].event.isRepeating())
		{
			result += events[i].event;
		}
	}

	for (size_t i = 0; i < cm; ++i)
	{
		if (meetings[i].meating.isRepeating())
		{
			result += meetings[i].meating;
		}
	}

	++this->month;

	std::swap(this->events, result.events);
	std::swap(this->ce, result.ce);

	std::swap(this->meetings, result.meetings);
	std::swap(this->cm, result.cm);

	std::swap(this->tasks, result.tasks);
	std::swap(this->ct, result.ct);

	return *this;
}

Calendar Calendar::operator++(int)
{
	Calendar old = *this;
	++(*this);
	return old;
}

std::ostream& operator<<(std::ostream& out, const Calendar& calendar)
{
	out << "Month: " << calendar.month << std::endl;

	out << "\nEvents:\n";
	for (size_t i = 0; i < calendar.ce; ++i)
	{
		out
			<< "Day: " << calendar.events[i].day << '\t'
			<< "Hour: " << calendar.events[i].hour << '\n'
			<< calendar.events[i].event << std::endl;
	}

	out << "\nTasks:\n";
	for (size_t i = 0; i < calendar.ct; ++i)
	{
		out
			<< "Day: " << calendar.tasks[i].day << '\t'
			<< "Hour: " << calendar.tasks[i].hour << '\n'
			<< calendar.tasks[i].task << std::endl;
	}

	out << "\nMeetings:\n";
	for (size_t i = 0; i < calendar.cm; ++i)
	{
		out
			<< "Day: " << calendar.meetings[i].day << '\t'
			<< "Hour: " << calendar.meetings[i].hour << '\n'
			<< calendar.meetings[i].meating << std::endl;
	}

	return out;
}
