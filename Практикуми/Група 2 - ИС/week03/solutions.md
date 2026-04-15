# Решения

### Задача 1
```cpp
int main()
{
	std::ifstream ifs("main.cpp");
	if (!ifs.is_open())
	{
		std::cout << "Error...";
		return -1;
	}
	while (!ifs.eof())
	{
		char buffer[100];
		ifs.getline(buffer, 100);
		std::cout << buffer << '\n';
	}
}
```

### Задача 2
Ако използвате вариант `1` (виж закоментирания код), ще видите че всеки път резултатът е с 1 повече. Това се случва, защото `eof` всъщност се активира **след първото неуспешно четене**. Но понеже при това първо неуспешно четене ние вече сме влязли в тялото на loop-a, броячът ще се инкрементира още веднъж.  
Вариант е (виж `2`) да вкараме проверката за `eof` вътре в цикъла, **след четенето, но преди брояча!** Не е много елегантно, но се разбира каква е идеята.
По-чисто (но и по трудно за разбиране) решение е `3`, където четенето ни е в условието за цикъла. Това работи, защото `stream >> y` и `stream << y` освен че четат/пишат, като резултат връщат обекта `stream`. Понеже е в условие за цикъл, което очаква стойност `bool`, имплицитно се конвертира (все едно `(bool)stream`). Потоците са реализирани така, че булевата им стойност отговаря на `good` флага им, което е много удобно за проверка. Все едно правим `while (ifs.good())`. `eof` флага смъква `good` флага, така че когато стигнем края на файла, цикълът ще приключи.
```cpp
int getWordCount(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << "Error! Could not open file!";
		return -1;
	}
	char buffer[100];
	unsigned counter = 0;

	//--1--
	//while (!ifs.eof())
	//{
	//	ifs >> buffer;
	//	counter++;
	//}

	//--2--
	// while (true)
	// {
	// 	ifs >> buffer;
	// 	if (ifs.eof()) break;
	// 	counter++;
	// }

	//--3--
	while (ifs >> buffer)
	{
		counter++;
	}

	return counter;
}
```

### Задача 3
Когато прочете последния ред, getline веднага вдига `eof` (за разлика от <<), така че тук не е проблем да си направим стандартната проверка.
```cpp
int getLineCount(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << "Error! Could not open file!";
		return -1;
	}
	char buffer[100];
	unsigned counter = 0;

	while (!ifs.eof())
	{
		ifs.getline(buffer, 100);
		counter++;
	}

	return counter;
}
```

### Задача 4
Ще коментрираме по-подробно тази задача по време на следващия практикум. **Тя е най-важната за писането на ООП код!**
```cpp
struct Student
{
	char name[32];
	unsigned year;
	float grade;
};

void readStudent(Student& st)
{
	std::cin >> st.name >> st.year >> st.grade;
}

void printStudent(const Student& st)
{
	std::cout << st.name << ' ' << st.year << ' ' << st.grade << '\n';
}

void storeStudent(const Student& st, std::ofstream& ofs)
{
	ofs << st.name << ' ' << st.year << ' ' << st.grade << '\n';
}

void readStudent1(Student& st, std::ifstream& ifs)
{
	ifs >> st.name >> st.year >> st.grade;
}

int main()
{
	{
		int n;
		std::cin >> n;
		Student* students = new (std::nothrow) Student[n];
		if (!students) return -1;
		for (int i = 0; i < n; i++)
		{
			readStudent(students[i]);
		}

		std::ofstream ofs("test.txt");
		if (!ofs.is_open()) return -1;

		ofs << n << '\n';
		for (int i = 0; i < n; i++)
		{
			storeStudent(students[i], ofs);
		}
		ofs.close();
		delete[] students;
	}


	{
		std::ifstream ifs("test.txt");
		if (!ifs.is_open()) return -1;
		int n;
		ifs >> n;
		Student* students = new Student[n];
		if (!students) return -1;
		for (int i = 0; i < n; i++)
		{
			readStudent1(students[i], ifs);
		}

		for (int i = 0; i < n; i++)
		{
			printStudent(students[i]);
		}
		delete[] students;
	}

}
```

### Задача 5
Буквално един ред разлика от задача 2. При всяка дума проверяваме дали е равна на подадената дума като параметър.
За целта използваме `strcmp` (string compare) от хедъра `cstring`. Това е вградена функция, която сравнява дали два низа са еднакви или не. Обърнете внимание, че при положителен отговор функцията връща `0`, което за булева стойност имплицитно се преобразува към `false`, за това добавяме `!` за да стане `true` и кода в `if`-a да се изпълни. (за любопитните - [документацията](https://en.cppreference.com/w/c/string/byte/strcmp))
```cpp
int getWordCount(const char* word, const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << "Error! Could not open file!";
		return -1;
	}
	char buffer[100];
	unsigned counter = 0;

	while (ifs >> buffer)
	{
		if (!strcmp(buffer, word))	//!
			counter++;
	}

	return counter;
}
```

### Задача 6
Ако игнорираме новите редове, това просто решение е достатъчно. Ако трябва да спазваме всеки нов ред на стария файл да е нов ред и на новия, ще трябва за всеки ред: да четем с getline(), да манипулираме всеки ред, да го запишем в другия файл.
```cpp
void replace(const char* fileName, const char* newFileName, const char* find, const char* replace)
{
	std::ifstream ifs(fileName);
	std::ofstream ofs(newFileName);
	if (!ifs.is_open() || !ofs.is_open())
	{
		std::cout << "Error! Could not open files!";
		return;
	}
	char buffer[100];
	while (ifs >> buffer)
	{
		if (!strcmp(buffer, find))	//!
		{
			ofs << replace << ' ';
		}
		else
		{
			ofs << buffer << ' ';
		}
	}
}
```

### Задача 7
```cpp
void getDiff(const char* file1, const char* file2)
{
	if (!strcmp(file1, file2))
	{
		std::cout << "They are the same file!'\n";
		return;
	}

	std::ifstream fs1(file1);
	std::ifstream fs2(file2);

	if (!fs1.is_open() || !fs2.is_open())
	{
		std::cout << "Error! Could not open files!";
		return;
	}

	char buffer1[200];
	char buffer2[200];
	unsigned counter = 1;

	while (!fs1.eof() && !fs2.eof())
	{
		fs1.getline(buffer1, 200);
		fs2.getline(buffer2, 200);
		if (strcmp(buffer1, buffer2))
		{
			std::cout << "Mismatch on line " << counter << ":\n";
			std::cout << buffer1 << '\n' << buffer2 << '\n';
			return;
		}
		counter++;
	}
	if (fs1.eof() && fs2.eof())
	{
		std::cout << "Files are identical!\n";
	}
	else if (fs1.eof())
	{
		std::cout << "file2 is longer!\n";
	}
	else
	{
		std::cout << "file1 is longer!\n";
	}
}
```

