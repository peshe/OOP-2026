#pragma once

#include "Event.h"
#include "Task.h"
#include "Meeting.h"

class Calendar
{
	friend std::ostream& operator<<(std::ostream& out, const Calendar& calendar);

	struct EventForDate
	{
		Event event;
		unsigned day;
		unsigned hour;
	};

	struct TaskForDate
	{
		Task task;
		unsigned day;
		unsigned hour;
	};

	struct MeetingForDate
	{
		Meeting meating;
		unsigned day;
		unsigned hour;
	};

	public:
		Calendar(unsigned month);
		Calendar(const Calendar& other);
		Calendar& operator=(const Calendar&) = delete;
		~Calendar();

		Calendar& operator+=(const Task& event);
		Calendar& operator+=(const Event& event);
		Calendar& operator+=(const Meeting& event);

		Calendar& operator-=(const char* name);

		Task* operator[] (const char*);
		const Task* operator[] (const char*) const;

		unsigned getMonth() const { return this->month; }

		size_t getCountTasks() const { return this->ct; }

		Calendar& operator++();
		Calendar operator++(int);

	private:
		void free();
		bool findFirstFreeHour(unsigned int& day, unsigned int& hour) const;

	private:
		unsigned month;

		EventForDate* events{};
		size_t ce{};

		TaskForDate* tasks{};
		size_t ct{};

		MeetingForDate* meetings{};
		size_t cm{};

		static const size_t COUNT_HOURS_IN_MONTH = 31 * 24;
		bool hours[COUNT_HOURS_IN_MONTH]{ false };
};

