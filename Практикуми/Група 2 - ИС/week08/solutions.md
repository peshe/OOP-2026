# Решения

### Задача 1
Използваме static променлива, която е обща за целия клас. id не трябва да се променя при никакви обстоятелства, за това го правим const и го инициализираме в инициализиращия списък на конструкторите. Забележете че в op= не променяме нищо. Данните може и да се променят, но обектът остава същия (съответно и id-то).  
Static променливата трябва да се инициализира извън дефиницията на класа (освен ако не е const).  
```cpp
class Student
{
public:
	Student()
		:Student("", 2000, 2)
	{
	}

	Student(const char* name, unsigned year, float grade)
		:id(counter++)		//!
	{
		setName(name);
		setYear(year);
		setGrade(grade);
	}

	Student(const Student& other)
		:grade(other.grade), year(other.year), id(counter++)	//!
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

//...

private:
	static unsigned counter;	//!

	const unsigned id;			//!
	char* name = nullptr;
	unsigned year;
	float grade;
};

unsigned Student::counter = 0;	//!
```

### Задача 2
Тази задача е добър пример за композиция на класове.  
Имаме два вътрешни класа, които участват в структурата на трети. Наблягам на взаимодействието на жизнения цикъл на обектите!  
CPU е стандартен клас с динамична памет и голяма четворка.  
Display е клас без динамична памет. **Това не значи че няма копиращ конструктор, оператор= и деструктор, значи, че default-ните, които компилтора генерира, ни вършат работа**.  
Laptop има динамична памет, съответно трябва да има голяма четворка. Тя обаче трябва да взаимодейства и с вложените класове и техните големи четворки. Ще коментирам всяка функция едно по едно:  
Ако в който и да е конструктор на външния клас не извикаме някой конструктор на вътрешния клас, то default конструктора му ще бъде извикан имплицитно. Когато пишем конструктора по конструктора по подразбиране (default c-tor) на външния клас, ние искаме точно това поведение, за това и не извикваме нищо. Само присвояваме brand.  
В конструктора с параметри подаваме всички параметри наведнъж и после викаме конструктора с параметри на cpu и display в инициализиращия списък. Накрая присвояваме и данните от външния клас (brand) с помощта на setter-а.  
За копиращия конструктор е аналогичнчо, викаме копиращите конструктори на вътрешните класове и после присвояваме brand.
При оператора за присвояване (op=) обаче става мазало. Имаме две неща, които могат да хвърлят изключение - setBrand() и op= на cpu. Ако просто ги изпълним едно след друго има риск първото да се изпълни и второто да хвърли изключение, което ще прекрати операцията и ще промени обекта частично (нарушава се strong exception safety) или по лошо - ще има memory leak.  
За да решим този проблем, трябва да ползваме try catch и да пренаредим стъпките малко. Това прави ползването ни на setter-a невъзможно. Кода става доста неелегантен и труден за четене. Този проблем лесно може да решим с `copy & swap idiom`, за който ще си говорим следващия път.  
При деструктора не е нужно да викаме деструкторите на вътрешните класове, компилатора ще го направи за нас. (всеки клас има един деструктор, няма какво да обърка)  

За опростение на примерното решение са пропуснати getter-и и setter-и, които не са нужни за задачата. Естествено, те трябва да присъстват за пълното решаване на задачата. Сериализацията в/от файлове също не е реализирана.
```cpp
class CPU
{
public:
	CPU()
		:CPU("", 1)
	{ }

	CPU(const char* model, float clockSpeed)
	{
		setModel(model);
		setClockSpeed(clockSpeed);
	}

	CPU(const CPU& other)
	{
		setModel(other.model);
		setClockSpeed(other.clockSpeed);
	}

	CPU& operator=(const CPU& other)
	{
		if (&other != this)
		{
			setModel(other.model);
			setClockSpeed(other.clockSpeed);
		}
		return *this;
	}

	~CPU()
	{
		delete[] model;
	}

	void setModel(const char* model)
	{
		if (!model) throw std::runtime_error("invalid model");
		int lenght = strlen(model);
		char* newStr = new char[lenght + 1] {};
		strcpy(newStr, model);
		delete[] this->model;
		this->model = newStr;
	}
	void setClockSpeed(float clockSpeed)
	{
		if (clockSpeed <= 0) throw std::runtime_error("invalid clock speed");
		this->clockSpeed = clockSpeed;
	}

	void print() const
	{
		std::cout << "CPU: " << model << ' ' << clockSpeed << "GHz\n";
	}

private:
	char* model;
	float clockSpeed;
};


class Display
{
public:
	Display()
		:Display(10,100,100)
	{ }

	Display(unsigned refreshRate, unsigned w, unsigned h)
		:refreshRate(refreshRate), width(w), heigth(h)
	{
		if (refreshRate == 0 || w == 0 || h == 0)
			throw std::runtime_error("invalid argument");
	}

	void print() const
	{
		std::cout << "Display: " << width << 'x' << heigth << ' ' << refreshRate << "hz\n";
	}
private:
	unsigned refreshRate;
	unsigned width;
	unsigned heigth;
};


class Laptop
{
public:
	Laptop()
		//!
	{ 
		setBrand("");
	}

	Laptop(
		const char* brand, const char* cpuModel, float clockSpeed,
		unsigned w, unsigned h, unsigned refreshRate)
		:cpu(cpuModel, clockSpeed), display(refreshRate, w, h)
	{
		setBrand(brand);
	}

	Laptop(const Laptop& other)
		:cpu(other.cpu), display(other.display)
	{
		setBrand(other.brand);
	}

	Laptop& operator=(const Laptop& other)
	{
		if (&other != this)
		{
			int lenght = strlen(other.brand);

			char* newStr = new char[lenght + 1] {};		//this can throw
			try
			{
				cpu = other.cpu;						//this can also throw
			}
			catch (...)
			{
				delete[] newStr;
				throw;
			}

			strcpy(newStr, other.brand);
			delete[] brand;
			brand = newStr;



			//instead of all the above code, this would be fine if we didnt have to worry about exceptions
			//setBrand(other.brand);
			//cpu = other.cpu;
			//we do need to worry about them though


			display = other.display;	//this will never throw so it's fine
		}
		return *this;
	}

	~Laptop()
	{
		delete[] brand;
	}

	void setBrand(const char* brand)
	{
		if (!brand) throw std::runtime_error("invalid brand");
		int lenght = strlen(brand);
		char* newStr = new char[lenght + 1] {};
		strcpy(newStr, brand);
		delete[] this->brand;
		this->brand = newStr;
	}

	void print() const
	{
		std::cout << "Laptop: " << brand << '\n';
		cpu.print();
		display.print();
	}

private:
	CPU cpu;
	Display display;
	char* brand;
};
```