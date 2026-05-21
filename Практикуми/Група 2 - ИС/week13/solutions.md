# Решения

### Пример за диамантен проблем с класовете от миналата седмица
```cpp
//we make the inheritance virtual

class Cat : virtual public Animal;
//...

class Dog : virtual public Animal;
//...

class CatDog : public Cat, public Dog
{
public:
	CatDog(const char* breed,
		const char* name,
		unsigned age)
		: Animal(name, age),    //with virtual inheritance, we have to call the constructor of the base class on our own
		Cat(breed, name, age),
		Dog(name, age)
	{}

	CatDog(const CatDog&other)
		: Animal(other),        //also here
		Cat(other),
		Dog(other)
	{}

	void print() const override
	{
		std::cout << "I am a CatDog\n";
	}

	void makeSound() const override
	{
		std::cout << "Meow-Arf\n";
	}

	Animal* clone() const override
	{
		return new CatDog(*this);
	}
};
```


### Задача 2
```cpp
class ScreenItem
{
public:
	ScreenItem(const char* title, bool movable)
		:movable(movable)
	{
		setTitle(title);
	}

	ScreenItem(const ScreenItem& other)
		:movable(other.movable)
	{
		setTitle(other.title);
	}

	ScreenItem& operator=(const ScreenItem& other)
	{
		if (this != &other)
		{
			setTitle(other.title);
			movable = other.movable;
		}
		return *this;
	}

	virtual ~ScreenItem() { delete[] title; }


	const char* getTitle() const { return title; }
	bool canMove() const { return movable; }

	virtual ScreenItem* clone() const = 0;

protected:
	char* title = nullptr;
	bool movable;

	void setTitle(const char* newTitle)
	{
		if (!newTitle) throw std::runtime_error(nullptr);
		char* copy = new char[strlen(newTitle) + 1];
		strcpy(copy, newTitle);
		delete[] this->title;
		title = copy;
	}

    //if we need to use copy and swap later
	void swap(ScreenItem& other)
	{
		std::swap(title, other.title);
		std::swap(movable, other.movable);
	}
};

class Screen
{
public:
	Screen(unsigned rows, unsigned cols)
		:rows(rows), cols(cols)
	{
		if (!rows || ! cols) throw std::runtime_error("invalid arg");
		items = new ScreenItem **[rows];
		for (int i = 0; i < rows; i++)
		{
			try
			{
				items[i] = new ScreenItem * [cols] {};
			}
			catch (const std::exception&)
			{
				for (int j = 0; j < i; j++)
				{
					delete[] items[j];
				}
				delete[] items;
				throw;
			}
		}
	}

    //virtual so we can override it in the folder class
	virtual bool addItem(const ScreenItem* item, unsigned k, unsigned l)
	{
		if (!item) throw std::runtime_error("nullptr");

		if (items[k][l] == nullptr)
		{
			items[k][l] = item->clone();
			return true;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (items[i][j] == nullptr) 
				{
					items[i][j] = item->clone();
					return true;
				}
			}
		}
		return false;
	}

    //virtual so we can override it in the folder class
	virtual bool removeItem(unsigned k, unsigned l)
	{
		if (items[k][l] == nullptr || !items[k][l]->canMove())
		{
			return false;
		}
		delete items[k][l];
		items[k][l] = nullptr;
	}

	bool moveElement(unsigned i, unsigned j, unsigned k, unsigned l)
	{
		if (items[i][j] != nullptr && items[i][j]->canMove())
		{
			if (items[k][l] == nullptr || items[k][l]->canMove())
			{
				std::swap(items[i][j], items[k][l]);
				return true;
			}
		}

		return false;
	}

	void clear()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				delete items[i][j];
				items[i][j] = nullptr;
			}
		}
	}

	~Screen()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				delete items[i][j];
			}
			delete[] items[i];
		}
		delete[] items;
	}

	friend std::ostream& operator<<(std::ostream& os, const Screen& screen);


protected:

	void swap(Screen& other)
	{
		std::swap(items, other.items);
		std::swap(rows, other.rows);
		std::swap(cols, other.cols);
	}

	ScreenItem*** items;
	unsigned rows;
	unsigned cols;
};


std::ostream& operator<<(std::ostream& os,const Screen& screen)
{
	for (int i = 0; i < screen.rows; i++)
	{
		for (int j = 0; j < screen.cols; j++)
		{
			std::cout << i << "," << j << " " << screen.items[i][j]->getTitle() << '\n';
		}
	}
	return os;
}


class MobileApp : public ScreenItem
{
public:
	MobileApp(const char* title)
		:ScreenItem(title, true)
	{
	}
	
};

class SystemWidget : public ScreenItem
{
	SystemWidget()
		:ScreenItem("System Widget", false)
	{ }
};


class Folder : public ScreenItem, public Screen
{
	Folder(unsigned rows, unsigned cols)
		:ScreenItem("", true), Screen(rows, cols)
	{
		updateName();
	}

	bool addItem(const ScreenItem* item, unsigned k, unsigned l) override
	{
		Screen::addItem(item, k, l);
		updateName();
	}

	bool removeItem(unsigned k, unsigned l) override
	{
		Screen::removeItem(k, l);
		updateName();
	}

protected:
	void updateName() {};	//TODO
};
```