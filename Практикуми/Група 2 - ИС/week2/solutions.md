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
``` c++

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