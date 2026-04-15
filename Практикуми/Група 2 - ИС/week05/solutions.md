# Решения

### Задача 1
За да дефинираме шаблон на функция започваме с `template<typename T>` При извикване на функцията, ще се генерира такава, където `T` ще бъде заместен със съответния тип на параметрите, които сме подали.  
Както при номралните функции, така и при шаблоните може да правим параметрите `const`, референции (`&`) или указатели (`*`). `const` пишем винаги, където можем.  
Референциите при примитивните типове не са нужни, ако са само с цел избягване на излишно копиране. Въпреки това ще ги пишем, защото шаблоните може да се извикват и с обекти, а там има значение. (ще го покажем по-късно)
```cpp
template<typename T>
T sum(const T& a, const T& b)
{
	return a + b;
}
```

### Задача 2
```cpp
template<typename T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
```

### Задача 3
Имаме стандартния шаблон за принтиране и специализацията за char*. Предполагаме че подадения масив от символи е валиден низ. Забележете как на първия шаблон имаме `const T* arr`. Това също е частична специализация, която ни ограничава до това да подаваме само указатели от тип `T` (все пак всеки масив е указател). Може да напишем и `const T arr`, и пак ще работи, но така позволяваме на шаблона да генерира функция с променливи, които не са указатели. Това винаги ще даде грешка при опит за компилация. (заради arr[i])
```cpp
template<typename T>
void print(const T* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << ' ';
	}
}

template<>
void print(const char* str, int n)
{
	std::cout << str;
}
```

### Задача 4
Дефинираме си 3 различни "placeholder-a" за типове. Те може да са различни, а може и да са еднакви. Показани са примерни извиквания в main(). Всички са валидни и се принтират на екрана.
```cpp
template<typename T, typename U, typename V>
void printThree(const T& a, const U& b, const V& c)
{
	std::cout << a << ' ' << b << ' ' << c << '\n';
}

int main()
{
	printThree(1, 2, 3);
	printThree(1, 2, 3.5);
	printThree(1, 2.5, "heyy");
}
```

### Задача 5
```cpp
template<typename T>
bool find(const T* arr, int size, const T& element)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
		{
			return true;
		}
	}
	return false;
}
```

### Задача 6
Разгледайте внимателно сигнатурата (т.е. редът преди тялото) на функцията. Бъдете сигурни че разбирате защо изглежда така. Забележете, че в указателя ми към функция параметърът ми е `const T&`, което значи, че всички функции, с които използваме filter, трябва също да са с `const T& параметър. Дадени са примерни извиквания в main.
```cpp
template<typename T>
T* filter(const T* arr, int size, bool (*pred)(const T&), int& newSize)
{
	if (!arr || !pred) return nullptr;
	newSize = 0;
	for (int i = 0; i < size; i++)
	{
		if (pred(arr[i]))
		{
			newSize++;
		}
	}
	T* newArr = new (std::nothrow) T[newSize];
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

bool isEven(const int& a)
{
	return a % 2 == 0;
}

int main()
{
	int* arr = new int[5] {1,2,3,4,5};
	int newSize = 0;
	int* arr2 = filter<int>(arr, 5, isEven, newSize);      //OK
	int* arr3 = filter(arr, 5, isEven, newSize);      //ALSO OK
	int* arr4 = filter<int>(arr, 5, [](const int& x){return (x % 2 == 0); }, newSize);  //ALSO OK
}
```
Нека разгледаме този интересен случай. Имаме шаблон на функция fold, която като параметър приема указател към функция `T (*f)(T,T)` с която да "сгъне" масива. Имаме и шаблона `sum` от първа задача. Може да ги комбинираме, като в извикването на fold директно подадем sum. Компилаторът ще генерира sum с правилния тип и fold ще го използва коректно. Нито определяме типа на fold, нито на sum. Яко, а? :D
```cpp
template<typename T>
T sum(const T& a, const T& b)
{
	return a + b;
}

template <typename T>
T fold(const T* arr, int size, const T& n, T (*f)(const T&, const T&))
{
	if (!arr || !f) return 0;
	T sum = n;
	for (int i = 0; i < size; i++)
	{
		sum = f(sum, arr[i]);
	}
	return sum;
}


int main()
{
	int* arr = new int[5] {1,2,3,4,5};
	double* arr2 = new double[3] {1.5, 2.5, 3.5};
	std::cout << fold(arr, 5, 0, sum);		//15
	std::cout << fold(arr2, 3, 0.0, sum);	//7.5
}
```