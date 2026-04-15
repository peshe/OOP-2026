# Решения

### Задача 1  
Основен пример за приемане на функция като параметър на друга функция и извикването и в нея.
``` c++
int countOfElemt(const int* arr, int size, bool (*pred)(int))
{
	if (!arr || !pred) return 0;
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			counter++;
		}
	}
	return counter;
}
```

### Задача 2
``` c++
int* filter(const int* arr, int size, bool (*pred)(int), int& newSize)
{
    if (!arr || !pred) return nullptr;
	for (int i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			newSize++;
		}
	}
	int* newArr = new (std::nothrow) int[newSize];
    if (!newArr) return nullptr;
    for (int i = 0, j = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			newArr[j++] = arr[i];
		}
	}
    return newArr;
}
``` 

### Задача 3
Идеята тук е, че въпреки, че имаме enum class с някакви имена, не можем да ги принтираме толкова лесно на екрана, защото те са само за програмистта, а в паметта се съхраняват целочислени стойности. Затова може да направим следния трик - да си създадем един масив от низове със същия ред като enum-a и да индексираме със стойността на променливата тип enum. Ако е enum class (както е препоръчително) ще трябва да cast-нем променливата експлицитно.
``` c++
enum class Suit
{
	UNKNOWN = -1,

	Clubs,
	Hearts,
	Spades,
	Diamonds,

	COUNT
};

const char* SUITS[] = {
	"Clubs",
	"Hearts",
	"Spades",
	"Diamonds"
};

const char* POWERS[] = {
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Jack",
	"Queen",
	"King",
	"Ace"
};

void printCard(Suit suit, int power)
{
	if (power < 2 || power > 14) return;
	std::cout << POWERS[power - 2] << " of " << SUITS[(int)suit] << '\n';
}
```

### Задача 4
``` c++
int fold(const int* arr, int size, int n, int (*f)(int, int))
{
	if (!arr || !f) return 0;
	int sum = n;
	for (int i = 0; i < size; i++)
	{
		sum = f(sum, arr[i]);
	}
	return sum;
}
```