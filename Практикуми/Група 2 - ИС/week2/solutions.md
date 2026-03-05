# Задачи

### Задача 1  
За да е нечетно едно цяло число, в бинарната му репрезентация, последният бит (най-десният) трябва да е `1`. Това го проверяваме като приложим операцията "и" (`&`) с числото и `0...01` (или просто 1). Това ще нулира всички останали цифри освен последната и ако последната е 1, ще ни върне 1. Ако последната е 0, ще ни върне 0. Тъй като искаме да видим дали числото е четно (а не нечетно) обръщаме резултата с `!`.
``` c++
bool isEven(int num)
{
	return !(num & 1);
}
```

### Задача 2  
Идеята е да ползваме `(1 << к)` за да получим число от типа `0..010..0` за да работим върху точния бит на позиция `k` и после с помощта на останалите побитови операции да постигнем нужната промяна в `num`.  
Като коментар са записани пълните записи вместо съкратения синтаксис. Правят едно и също.
``` c++
void setBit(unsigned char& num, int k)
{
	num |= (1 << k);
	//num = num | (1 << k);
}

void clearBit(unsigned char& num, int k)
{
	num &= ~(1 << k);
	//num = num & ~(1 << k);
}

void flipBit(unsigned char& num, int k)
{
	num ^= (1 << k);
	//num = num ^ (1 << k);
}

bool getBit(unsigned char num, int k)
{
	return num & (1 << k);
}
```

### Задача 3  
Идеята е да shift-ваме числото надясно (делим на 2) и всеки път да проверяваме последния бит. Ако е 1, значи числото не е степен на двойката. Връщаме `true` точно тогава, когато числото стане точно `1`.
``` c++
bool isPowerOf2(unsigned num)
{
	if (num == 0) return false;
	
	while (num != 1)
	{
		if (num & 1) return false;
		num = num >> 1;
	}
	return true;
}
```

### Задача 4
``` c++
struct ComplexNum
{
	double real;
	double imag;
};

ComplexNum createComplexNum(double r, double i)
{
	ComplexNum num = { r, i };
	return num;
    //	return { r, i };    //alternative for the above 2 rows
}

void printComplexNum(const ComplexNum& num)
{
	std::cout << "(" << num.real << " + " << num.imag << "i)\n";
}

ComplexNum sumComplexNums(const ComplexNum& num1, const ComplexNum& num2)
{
	ComplexNum res = { num1.real + num2.real, num1.imag + num2.imag };
	return res;
}

double mod(const ComplexNum& num)
{
	return sqrt(num.real * num.real + num.imag * num.imag);
}

ComplexNum prodComplexNums(const ComplexNum& num1, const ComplexNum& num2)
{
	ComplexNum prod = {
        num1.real * num2.real - num1.imag * num2.imag,
        num1.real * num2.imag + num1.imag * num2.real
        };
	return prod;
}
```

### Задача 5
``` c++
enum class Major
{
	UNKNOWN = -1,

	IS,
	CS,
	SE,
	I,
	AM,
	M,
	
	COUNT
};

const char* majorToText(Major major)
{
	switch (major)
	{
	case Major::UNKNOWN:
		return "Unknown";
	case Major::IS:
		return "IS";
	case Major::CS:
		return "CS";
	case Major::SE:
		return "SE";
	case Major::I:
		return "I";
	case Major::AM:
		return "AM";
	case Major::M:
		return "M";
	default:
		return "Invalid";
	}
}

struct Student
{
    char name[32];
	unsigned year;
	Major major;
	float grade;
};

void readStudent(Student& student)
{
	int major;	//a better idea is to have a separate function that reads a string and returs the corresponding enum value.
	std::cin >> student.name >> student.year >> major >> student.grade;
	student.major = (Major)major;
}

void printStudent(const Student& student)
{
	std::cout << "Name: " << student.name << ", year: " << student.year 
			  << ", Major: " << majorToText(student.major) << ", Grade: " << student.grade << '\n';
}

float getAvgGrade(const Student students[], int studCount)
{
	double sum = 0;
	for (int i = 0; i < studCount; i++)
	{
		sum += students[i].grade;
	}
	return sum / studCount;
}
```

### Задача 6
Използването на битови полета ни смалява размера на структурата `Date` от 12 на 4 байта! Забележете как не може да подадем директно `date.day` на `std::cin` и за това ни трябва буфер в който да прочетем от конзолата и след това да присвоим стойността.
``` cpp
struct Date
{
	unsigned day : 5;
	unsigned month : 4;
	unsigned year : 23;
};

void readDate(Date& date)
{
	unsigned buffer;
	std::cin >> buffer;
	date.day = buffer;
	std::cin >> buffer;
	date.month = buffer;
	std::cin >> buffer;
	date.year = buffer;
}

void printDate(const Date& date)
{
	std::cout << "Day: " << date.day << " Month: " << date.day << " Year: " << date.day << '\n';
}
```

### Задача 7
Наблягам на заделянето на динамична памет за името:
1. Прочитаме в буфер от конзолата
2. Намираме дължината на прочетения низ
3. Заделяне на динамична памет
4. Проверка за успешно заделяне
5. Копиране на низа от буфера в новозаделената памет

Обърнете внимание как в структурата си ползваме друга, вече дефинирана структура.  
Също за реализирането на функцията `read/printGame` използваме `read/printDate`. По този начин преизползваме логика, правим кода си по-четим и не оставяме една фунцкия да върши твърде много работа.  
Реализирането на останалите фунцкии е горе-долу еднотипно.  
Обърнете внимание на заделянето на масива и изтриването на паметта в `main`.  
За `read/printGame` е изпуснат enum-a нарочно. Досадно е да се минава от enum в низ и обратното, вече сме го правили и се надявам да можете сами. Фокуса на задачата беше друг.

```cpp
#include <cstring>	//for strcpy and strlen
#pragma warning (disable : 4996)	//for visual studio to stop crying

enum class Genre
{
	UNKNOWN = -1,

	RPG,
	MMO,
	MOBA,

	COUNT
};


struct Game
{
	char* name;
	Date releaseDate;
	int ageRating;
	Genre genre;
	float price;
};

void readGame(Game& game)
{
	char buffer[100];
	std::cin >> buffer;
	int nameLen = strlen(buffer);
	game.name = new (std::nothrow) char[nameLen + 1] {};
	if (!game.name)
	{
		return;
	}
	strcpy(game.name, buffer);
	readDate(game.releaseDate);
	std::cin >> game.ageRating >> game.price;
}

void printGame(const Game& game)
{
	std::cout << game.name << '\n';
	printDate(game.releaseDate);
	std::cout << game.ageRating << '\n' << game.price << '\n';
}

void deleteGame(Game& game)
{
	delete[] game.name;
}

void printMostExpensive(const Game* games, int n)
{
	if (!games) return;
	int mostExp = 0;
	for (int i = 0; i < n; i++)
	{
		if (games[i].price > games[mostExp].price)
		{
			mostExp = i;
		}
	}
	printGame(games[mostExp]);
}

void printWithCensor(const Game* games, int n, unsigned playerAge)
{
	if (!games) return;
	for (int i = 0; i < n; i++)
	{
		if (games[i].ageRating <= playerAge)
		{
			printGame(games[i]);
		}
	}
}

void printFromYear(const Game* games, int n, int year)
{
	if (!games) return;
	for (int i = 0; i < n; i++)
	{
		if (games[i].releaseDate.year == year)
		{
			printGame(games[i]);
		}
	}
}

void printWithGenre(const Game* games, int n, Genre genre)
{
	if (!games) return;
	for (int i = 0; i < n; i++)
	{
		if (games[i].genre == genre)
		{
			printGame(games[i]);
		}
	}
}


int main()
{
	int n;
	std::cin >> n;
	Game* games = new (std::nothrow) Game[n];
	if (!games) return -1;

	for (int i = 0; i < n; i++)
	{
		readGame(games[i]);
	}
	printMostExpensive(games, 3);
	printWithCensor(games, 3, 18);

	printFromYear(games, 3, 2000);
	printWithGenre(games, 3, Genre::MMO);

	for (int i = 0; i < n; i++)
	{
		deleteGame(games[i]);
	}
	delete[] games;
}
```