# Решения

### Задача 0
При конструктора с параметри най-лесно е да използваме вече написаните ни setter-и. Вместо да пишем логиката за валидиране на данните в новия обект, си ползваме вече готовата. Важно е обаче, да отбележим, че ако бяха останали само с `return` при грешка, това нямаше да ни върши работа. За това хвърляме изключение, за да сме сигурни, че при невалидни данни конструкторът ще се прекрати и обектът няма да се създаде.
```cpp
#include <stdexcept> //for std::runtime_error

//...

	Student(const char* name, unsigned year, float grade)
	{
		setName(name);
		setYear(year);
		setGrade(grade);
	}

    void setName(const char* newName)
	{
		if (!newName || strlen(newName) > 31)
		{
			throw std::runtime_error("invalid name");
		}
		strcpy(name, newName);
	}

	void setYear(unsigned year)
	{
		if (year > 2026) throw std::runtime_error("invalid year");
		this->year = year;
	}

	void setGrade(float grade)
	{
		if (grade < 2 || grade > 6) throw std::runtime_error("invalid grade");
		this->grade = grade;
	}

    //...
```

### Задача 1
Обърнете внимание на следните неща:  
- За конструктора с параметри използваме сетърите за всяка, член данна, защото те ни осигуряват валидация на данните, което е жизнено важно!!!  
- За конструктора по подразбиране правя делегиране на конструктор, като извиквам конструктора с параметри (в инициализиращия списък) с дефаултни стойности (вместо да ги присвоявам една по една)  
- в копиращия конструктор мога да си позволя да ползвам инициализиращия списък, понеже данните вече са ми валидирани (все пак идват от друг обект, който трябва да е валиден (ако си спазваме ООП принципите ест))  
-оператор= винаги е хубаво да започва с реда `if (&other == this) return *this;`, който предотварятва излишно копиране на данни, ако се направи нещо като `student = student`. Също и винаги **трябва** да завършва с `return *this`, това е с цел да може да се chain-ва (т.е. `a = b = c`), повече за това, когато учим предефиниране на оператори.  
- в setName, понеже работим с динамична памет, първо заделяме памет за новото име, после копираме името от параметъра в новозаделената памет, изтриваме старата памет, и след това пренасочваме `this->name` към новото име. Тази последователност от стъпки е важна, защото ако първо изтрием старата памет и после директно заделим новата в указателя `this->name`, ако това заделяне не успее, ние сме изгубили старото име. И по-лошо, тогава `this->name` остава указател към вече изтрита памет, което всички знаем, че не е добре. Може да се замислим, дали не е проблем да викаме delete[] на указател, който още не е инициализиран (както правим в конструкторите). Не е проблем, когато указателя е `nullptr`. За това, ако ще ползваме setter по този начин в конструктора, винаги като default-на стойност на указателя задаваме nullptr.  
- getter-a `getName()` задължително трябва да връща **const** char*, за да не може външният свят да манипулира името ни през getter-a. Ако го оставим само char*, неща от типа: `student.getName()[0] = 'P';` ще променят името на студента, което очевидно не искаме да се случва (по този начин, има си setter-и за тая работа)
```cpp
class Student
{
public:

	/* this is ok
	Student()
		:year(2000), grade(2)
	{
		setName("");
	}
	*/
	//but this is better
	//		|
	//		V
	Student()
		:Student("", 2000, 2)
	{}

	Student(const char* name, unsigned year, float grade)
	{
		setName(name);
		setYear(year);
		setGrade(grade);
	}

	Student(const Student& other)
		:grade(other.grade), year(other.year)
	{
		setName(other.name);
	}

	Student& operator=(const Student& other)
	{
		if (&other == this) return *this;
		setName(other.name);
		year = other.year;
		grade = other.grade;
		return *this;
	}

	~Student()
	{
		delete[] name;
	}

	void setName(const char* name)
	{
		if (!name) throw std::runtime_error("invalid name");
		int lenght = strlen(name);
		char* newStr = new char[lenght + 1] {};
		strcpy(newStr, name);
		delete[] this->name;
		this->name = newStr;
	}

	void setYear(unsigned year)
	{
		if (year > 2026) throw std::runtime_error("invalid year");
		this->year = year;
	}

	void setGrade(float grade)
	{
		if (grade < 2 || grade > 6) throw std::runtime_error("invalid grade");
		this->grade = grade;
	}

	const char* getName() const { return name; }
	unsigned getYear() const { return year; }
	float getGrade() const { return grade; }

	void printStudent() const
	{
		std::cout << name << ' ' << year << ' ' << grade << '\n';
	}

private:
	char* name = nullptr;	//!!!
	unsigned year;
	float grade;
};
```