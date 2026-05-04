# Решения

### Задача 1
Спазваме конвенцията, че операторите тип `+=` дефинираме вътре в класа, а операторите тип `+` дефинираме отвън.  
Много е важно да дефинираме операторите по "комплекти" като преизползваме логиката на 1 оператор за всички останали в този комплект. Примерно с += може да дефинираме +, с < може да дефинираме >, <=, >= и тн. Не е важно кой ще е първия (в кой ще е логиката), важното е да изберем един и да го използваме за всички останали.  
Забележете двата [] оператора, единия е константен и връща копие (Пр: `int a = vec[0]`), другия не е константен и връща референция (Пр: `vec[0] = 5`).  
Забележете също и как с наличието на подходящ интерфейс на класа, не е нужно да дефинираме операторите << и >> като friend.  
Обърнете внимание и на разликата между prefix ++ и postfix ++.  
Всички оператори са дефинирани по "комплекти", където е възможно.  
**Тази задача горе долу покрива всички важни оператори по темата в курса.**  
```cpp
#include <iostream>
#include <cassert>  //for assert


class MathVec
{
public:
	MathVec& operator+=(const MathVec& other)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] += other.arr[i];
		}
	}


	MathVec& operator-=(const MathVec& other)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] -= other.arr[i];
		}
	}


	MathVec& operator*=(int scalar)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] *= scalar;
		}
	}


	MathVec& operator*=(const MathVec& other)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] *= other.arr[i];
		}
	}


	unsigned operator()() const
	{
		return n;
	}


	int operator[](unsigned index) const
	{
		assert(index < n);
		return arr[index];
	}


	int& operator[](unsigned index)
	{
		assert(index < n);
		return arr[index];
	}


	operator bool() const
	{
		for (int i = 0; i < n; i++)
		{
			if (arr[i] != 0)
				return true;
		}
		return false;
	}


	MathVec& operator++()   //prefix
	{
		for (int i = 0; i < n; i++)
		{
			arr[i]++;
		}
		return *this;
	}


	MathVec operator++(int) //postfix
	{
		MathVec copy(*this);
		for (int i = 0; i < n; i++)
		{
			arr[i]++;
		}
		return copy;
	}


private:
	static const unsigned n = 3;
	int arr[n]{};
};



MathVec operator+(const MathVec& l, const MathVec& r)
{
	MathVec copy(l);
	return copy += r;
}


MathVec operator-(const MathVec& l, const MathVec& r)
{
	MathVec copy(l);
	return copy -= r;
}


MathVec operator*(const MathVec& vec, int scalar)
{
	MathVec copy(vec);
	return copy *= scalar;
}


MathVec operator*(const MathVec& l, const MathVec& r)
{
	MathVec copy(l);
	return copy *= r;
}


std::istream& operator>>(std::istream is, MathVec& vec)
{
	for (int i = 0; i < vec(); i++)
	{
		is >> vec[i];
	}
}


std::ostream& operator<<(std::ostream os, const MathVec& vec)
{
	for (int i = 0; i < vec(); i++)
	{
		os << vec[i] << ' ';
	}
	std::cout << '\n';
}


bool operator==(const MathVec& l, const MathVec& r)
{
	for (int i = 0; i < l(); i++)
	{
		if (l[i] != r[i])
			return false;
	}
	return true;
}


bool operator!=(const MathVec& l, const MathVec& r)
{
	return !(l == r);
}


bool operator<(const MathVec& l, const MathVec& r)
{
	for (int i = 0; i < l(); i++)
	{
		if (l[i] != r[i])
			return l[i] < r[i];
	}
	return false;
}


bool operator>=(const MathVec& l, const MathVec& r)
{
	return !(l < r);
}


bool operator>(const MathVec& l, const MathVec& r)
{
	return r < l;
}


bool operator<=(const MathVec& l, const MathVec& r)
{
	return !(r < l);
}
```