# Задачи 

### Задача 1
```cpp
class Animal
{
public:
	Animal(const char* name, unsigned age)
		:age(age)
	{
		setName(name);
	}

	Animal(const Animal& other)
		:Animal(other.name, other.age)
	{ }

	Animal& operator=(const Animal& other)
	{
		if (this != &other)
		{
			setName(other.name);
			age = other.age;
		}
		return *this;
	}

	virtual ~Animal()
	{
		delete[] name;
	}

	void setName(const char* newName)
	{
		if (!newName) throw std::runtime_error("bad alloc");
		char* temp = new char[strlen(newName) + 1];
		strcpy(temp, newName);
		delete[] name;
		name = temp;
	}
	const char* getName() const
	{
		return name;
	}

	//a virtual function can have a body (outside the class) and it can be useful
	virtual void print() const = 0;
	virtual void makeSound() const = 0;
	virtual Animal* clone() const = 0;
protected:
	char* name = nullptr;
	unsigned age;

	void swap(Animal& other)
	{
		std::swap(name, other.name);
		std::swap(age, other.age);
	}
};

void Animal::print() const
{
	std::cout << "I am an animal\n";
}

class Cat : public Animal
{
public:
	Cat(const char* breed, const char* name, unsigned age)
		:Animal(name, age)
	{
		setBreed(breed);
	}

	Cat(const Cat& other)
		:Cat(other.breed, other.name, other.age)
	{ }

	Cat& operator=(const Cat& other)
	{
		if (&other != this)
		{
			Cat copy(other);
			Animal::swap(copy);
			std::swap(breed, copy.breed);
		}
		return *this;
	}

	void print() const override
	{
		Animal::print();
		std::cout << "Cat with breed: " << breed << '\n';
	}

	void makeSound() const override
	{
		std::cout << "meow\n";
	}

	Animal* clone() const override
	{
		return new Cat(*this);
	}

	~Cat()
	{
		delete[] breed;
	}

	void setBreed(const char* newBreed)
	{
		if (!newBreed) throw std::runtime_error("bad alloc");
		char* temp = new char[strlen(newBreed) + 1];
		strcpy(temp, newBreed);
		delete[] breed;
		breed = temp;
	}
private:
	char* breed = nullptr;
};

class Dog : public Animal
{
public:
	Dog(const char* name, unsigned age)
		:Animal(name, age)
	{ }

	void print() const override
	{
		Animal::print();
		std::cout << "I'm a dog\n";
	}
	void makeSound() const override
	{
		std::cout << "Arf\n";
	}
	Animal* clone() const override
	{
		return new Dog(*this);
	}
};


class PetShop
{
public:
	PetShop(unsigned maxCap)
		:maxCap(maxCap)
	{
		if (maxCap == 0) throw std::runtime_error("invalid cap");
		animals = new Animal * [maxCap] {};
		size = 0;
	}

	PetShop(const PetShop& other)
		:size(other.size), maxCap(other.maxCap)
	{
		animals = new Animal * [maxCap] {};
		for (int i = 0; i < size; i++)
		{
			try
			{
				animals[i] = other.animals[i]->clone();
			}
			catch (...)
			{
				for (int j = 0; j < i; j++)
				{
					delete animals[j];
				}
				delete[] animals;
				throw;
			}
		}
	}

	PetShop& operator=(const PetShop& other)
	{
		if (this != &other)
		{
			PetShop temp(other);
			std::swap(animals, temp.animals);
			std::swap(maxCap, temp.maxCap);
			std::swap(size, temp.size);
		}
		return *this;
	}

	~PetShop()
	{
		for (int i = 0; i < size; i++)
		{
			delete animals[i];
		}
		delete[] animals;
	}

	void addAnimal(Animal* animal)
	{
		if (size == maxCap) throw std::runtime_error("no space");
		if (!animal) throw std::runtime_error("invalid arg");
		animals[size] = animal->clone();
		size++;
	}

	void removeAnimal(const char* name)
	{
		if (!size) throw std::runtime_error("empty");
		for (int i = 0; i < size; i++)
		{
			if (strcmp(name, animals[i]->getName()) == 0)
			{
				delete animals[i];
				for (int j = i; j < size - 1; j++)
				{
					animals[j] = animals[j + 1];
				}
				i--;
				size--;
			}
		}
	}

	void makeSound() const
	{
		for (int i = 0; i < size; i++)
		{
			animals[i]->makeSound();
		}
		std::cout << '\n';
	}

	void print() const
	{
		for (int i = 0; i < size; i++)
		{
			animals[i]->print();
		}
		std::cout << '\n';
	}

	unsigned getSize()
	{
		return size;
	}

	unsigned getCap()
	{
		return maxCap;
	}

private:
	unsigned maxCap;
	unsigned size;
	Animal** animals;
};

int main()
{
	Animal* cat = new Cat("siamska", "gosho", 5);
	Animal* dog = new Dog("pesho", 5);
	PetShop shop(10);
	shop.addAnimal(cat);
	shop.addAnimal(cat);
	shop.addAnimal(dog);
	shop.addAnimal(cat);
	shop.makeSound();
	shop.print();
}
```