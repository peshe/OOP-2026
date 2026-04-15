# Решения

### Задача 1
Обърнете внимание на следните неща:  
-всяка функция (getter-ите задължително), която може да е const, е const.  
-валидацията на член-данните се извършва в setter-ите  
-в default конструктора задаваме дефаултни ***валидни*** данни.  (с помощта на setter)
``` cpp
#include <iostream>

#pragma warning (disable : 4996)

class Student
{
public:
	Student()
	{
		setName("");	//this will just do name[0] = '\0';
		year = 2000;
		grade = 2;
	}

	const char* getName() const { return name; }
	unsigned getYear() const { return year; }
	float getGrade() const { return grade; }

	void setName(const char* newName)
	{
		if (!newName || strlen(newName) > 31) return;
		strcpy(name, newName);
	}

	void setYear(unsigned year)
	{
		if (year > 2026) return;
		this->year = year;
	}

	void setGrade(float grade)
	{
		if (grade < 2 || grade > 6) return;
		this->grade = grade;
	}
	
	void printStudent() const
	{
		std::cout << name << ' ' << year << ' ' << grade << '\n';
	}
	bool canGetScolarship(float minGrade) const { return grade >= minGrade; }
	int getYearInUni(unsigned currYear) const { return currYear - year - 19; }
private:
	char name[32];
	unsigned year;  //birthYear
	float grade;
};
```

### Задача 2
``` cpp
#include <iostream>

class Date
{
public:
	Date()
	{
		day = 1;
		month = 1;
		year = 1970;
	}

	unsigned getDay() const { return day; }
	unsigned getMonth() const { return month; }
	unsigned getYear() const { return year; }

	void setDay(unsigned day)
	{
		if (day > 31 || day == 0) return;
		this->day = day;
	}
	void setMonth(unsigned month)
	{
		if (month > 12 || month == 0) return;
		this->month = month;
	}
	void setYear(unsigned year)
	{
		if (year == 0) return;
		this->year = year;
	}

	void print() const
	{
		std::cout << day << '.' << month << '.' << year << '\n';
	}

	void passDay()
	{
		if (day == 31)
		{
			passMonth();
			day = 1;
		}
		else
			day++;
	}
	void passMonth()
	{
		if (month == 12)
		{
			passYear();
			month = 1;
		}
		else
			month++;
	}
	void passYear() { year++; }
	bool isSummerBreak() { return month >= 7 && month <= 9; }

private:
	unsigned day;
	unsigned month;
	unsigned year;
};

//класът Time е аналогичен
```

### Задача 3
фокусът на задачите не е правене на контейнер (масив) от обекти, какъвто е GamePlatform, така че качвам само Game.
``` cpp
class Game
{
public:
	Game()
	{
		setTitle("");
		price = 0;
		available = false;
	}

	const char* getTitle() const { return title; }
	float getPrice() const { return price; }
	bool isAvailable() const { return available; }

	void setTitle(const char* newTitle)
	{
		if (!newTitle || strlen(newTitle) > 63) return;
		strcpy(title, newTitle);
	}
	void setPrice(float price)
	{
		if (price < 0) return;
		this->price = price;
	}
	void setAvailability(bool isAvailable)
	{
		available = isAvailable;
	}
	void print() const
	{
		std::cout << title << ' ' << price << ' ' << available << '\n';
	}
	bool isFree() { return price == 0; }

private:
	char title[64];
	float price;
	bool available;
};
```