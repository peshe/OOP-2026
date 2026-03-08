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