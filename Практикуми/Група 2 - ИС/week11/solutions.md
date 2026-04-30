# Решения

### Задача 1
Базовият клас има един динамично заделен низ и стандартна голяма четворка.  
Наследникът `Bicycle` няма динамична памет. Ако не напишем ние методите от голямата четворка, то тези генерирани от компилатора ще извикат имплицитно съответните методи от голямата четворка на базовия клас. Това значи, че в случая не е нужно да разписваме четворката за този клас. Той ще се грижи за динамичната памет на базовия си клас автоматично.  
Другият наследник `Car` обаче има динамична памет. Това значи, че ние задължително трябва да напишем голяма четворка за него. Докато я пишем, за всеки метод от нея трябва да викнем съответния метод от базовия клас **експлицитно** (както беше и при композицията на обекти).  
Забележете проблема при operator= на `Car`. Както казахме, трябва да викнем и operator= на базовия клас. Това прави реда `Vehicle::operator=(other)`. Той обаче може да хвърли изключение. setModel() също може да хвърли изключение. Получаваме класическия проблем, в който не може да използваме сетъра и трябва да ползваме try... catch. Един доста лесен начин да решим този проблем е с copy & swap идиома. Забележете, че в `Car::swap` викаме `Vehicle::swap`. Запазваме ООП идеята, че всеки клас си отговаря за неговата логика и че може да я преизползваме където ни трябва.  
Също забележете, че използвахме модификатора на достъп `protected`, за да може да достъпим член-данните в наследниците, но все пак да останат скрити за външния свят.

Когато подаваме обект от тип `Car` на функция която приема обект от тип `Vehicle` (в нашия случай в copy c-tor и op= на Car) правим *slicing* на обекта.
```cpp
class Vehicle
{
public:
	Vehicle(const char* brand, unsigned year, unsigned maxSpeed)
	{
		setBrand(brand);
		setYear(year);
		setMaxSpeed(maxSpeed);
	}

	Vehicle(const Vehicle& other)
		:Vehicle(other.brand, other.year, other.maxSpeed)
	{
	}

	Vehicle& operator=(const Vehicle& other)
	{
		if (this != &other)
		{
			setBrand(other.brand);
			setYear(other.year);
			setMaxSpeed(other.maxSpeed);
		}
		return *this;
	}

	~Vehicle()
	{
		delete[] brand;
	}

	void setYear(unsigned newyear) { year = newyear; }
	void setMaxSpeed(unsigned newMaxSpeed) { maxSpeed = newMaxSpeed; }

	void setBrand(const char* newBrand)
	{
		if (!newBrand) throw std::runtime_error("nullptr");
		char* temp = new char[strlen(newBrand) + 1] {};
		strcpy(temp, newBrand);
		delete[] brand;
		brand = temp;
	}

	const char* getBrand() { return brand; }
	unsigned getYear() { return year; }
	unsigned getMaxSpeed() { return maxSpeed; }

	void swap(Vehicle& other)
	{
		std::swap(brand, other.brand);
		std::swap(year, other.year);
		std::swap(maxSpeed, other.maxSpeed);
	}

protected:
	char* brand = nullptr;
	unsigned year;
	unsigned maxSpeed;
};


class Bicycle : public Vehicle
{
public:
	Bicycle(const char* brand, unsigned year, unsigned maxSpeed,
		unsigned numOfGears, bool hasRing)
		:Vehicle(brand, year, maxSpeed)
	{
		setNumOfGears(numOfGears);
		setRingAvailability(hasRing);
	}

	bool isNew() const { return year > 2016; }

	void setNumOfGears(unsigned newNumOfGears) { numOfGears = newNumOfGears; }
	void setRingAvailability(bool hasRing) { this->hasRing = hasRing; }

	unsigned getNumOfGears() const { return numOfGears; }
	bool ringAvailable() const { return hasRing; }


private:
	unsigned numOfGears;
	bool hasRing;
};


class Car : public Vehicle
{
	Car(const char* brand, unsigned year, unsigned maxSpeed,
		const char* model, unsigned power)
		:Vehicle(brand, year, maxSpeed)
	{
		setModel(model);
		setPower(power);
	}

	Car(const Car& other)
		:Vehicle(other)
	{
		setModel(other.model);
		setPower(other.power);
	}

	Car& operator=(const Car& other)
	{
		if (this != &other)
		{
			//we cant just do
			//setModel(other.model);
			//Vehicle::operator=(other);
			//if we want strong exception safety

			char* temp = new char[strlen(other.model) + 1] {};
			try
			{
				Vehicle::operator=(other);
			}
			catch (...)
			{
				delete[] temp;
				throw;
			}
			strcpy(temp, other.model);
			delete[] model;
			model = temp;

			setPower(other.power);

			//its simpler to use copy & swap
			//Car copy(other);
			//swap(copy);
		}
		return *this;
	}

	~Car()
	{
		delete[] model;
	}

	bool canGoOntheHighway() const { return maxSpeed >= 50; }

	void setModel(const char* newModel)
	{
		if (!newModel) throw std::runtime_error("nullptr");
		char* temp = new char[strlen(newModel) + 1] {};
		strcpy(temp, newModel);
		delete[] model;
		model = temp;
	}

	void setPower(unsigned newPower) { power = newPower; }

	const char* getModel() const { return model; }
	unsigned getPower() const { return power; }

	void swap(Car& other)
	{
		Vehicle::swap(other);
		std::swap(model, other.model);
		std::swap(power, other.power);
	}

private:
	char* model;
	unsigned power;
};
```