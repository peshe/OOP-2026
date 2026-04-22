#include "Bookshelf.h"

Bookshelf::Bookshelf(unsigned countShelves, unsigned pagesMaxCount)
	: numberOfShelves(countShelves)
{
	try
	{
		this->shelves = new Shelf[numberOfShelves]{ };
		for (size_t i = 0; i < numberOfShelves; ++i)
		{
			this->shelves[i].setMaxNumberOfPages(pagesMaxCount);
			this->shelves[i].attachToBookshelf(this, i);
		}
	}
	catch (...)
	{
		delete[] this->shelves;
		throw;
	}
}

Bookshelf::~Bookshelf()
{
	delete[] this->shelves;
}

const Book* Bookshelf::findBook(const char* name) const
{
	if (!name)
		return nullptr;

	for (size_t i = 0; i < this->numberOfShelves; ++i)
	{
		int pos = this->shelves[i].findBook(name);
		if (pos >= 0)
		{
			const Book* book = this->shelves[i].at(pos);
			return book;
		}
			
	}

	return nullptr;
}

bool Bookshelf::addBook(Book& book)
{
	int index = this->numberOfShelves - 1;
	while (index >= 0)
	{
		if (this->shelves[index].addBook(book))
			return true;

		--index;
	}

	return false;
}

bool Bookshelf::removeBook(const Book& book)
{
	for (size_t i = 0; i < this->numberOfShelves; ++i)
	{
		if (this->shelves[i].removeBook(book))
			return true;
	}

	return false;
}

bool Bookshelf::changeShelvesSize(unsigned newSize)
{
	for (size_t i = 0; i < this->numberOfShelves; ++i)
	{
		if (!this->shelves[i].setMaxNumberOfPages(newSize))
			return false;
	}

	return true;
}

void Bookshelf::print() const
{
	for (size_t i = 0; i < this->numberOfShelves; ++i)
	{
		std::cout << "--- Shelf [" << i << "] ---\n";
		this->shelves[i].print();
	}
}
