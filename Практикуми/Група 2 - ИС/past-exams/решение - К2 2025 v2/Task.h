#pragma once
#include "Event.h"

struct Date
{
    unsigned day, month;
    Date(unsigned d = 1, unsigned m = 1) 
        : day(d), month(m) 
    { }
};

bool operator<(const Date& left, const Date& right);
bool operator<=(const Date& left, const Date& right);
bool operator>(const Date& left, const Date& right);
bool operator>=(const Date& left, const Date& right);
bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);

std::ostream& operator<<(std::ostream& out, const Date& date);
std::istream& operator>>(std::istream& out, const Date& date);

class Task: public Event
{
public:
    Task() = default;
    Task(
        const char* name, 
        const char* description, 
        unsigned length, 
        bool repeating, 
        const Date& date
    );

    Date getDate() const { return this->date; }
    void setDate(const Date& date);

private:
    Date date;
};

bool operator>(const Task& left, const Task& right);
bool operator>=(const Task& left, const Task& right);
bool operator<(const Task& left, const Task& right);
bool operator<=(const Task& left, const Task& right);

std::ostream& operator<<(std::ostream& out, const Task& task);
std::istream& operator>>(std::istream& out, Task& task);