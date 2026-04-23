#include <cassert>

#include "Bookshelf.h"
#include "Shelf.h"

Shelf::Shelf(unsigned pagesMaxCount) :
	bookshelf(nullptr), position(0),
	books(nullptr), used(0), allocated(1), 
	pagesMaxCount(pagesMaxCount), currentPagesCount(0)
{
	books = new Book * [allocated] {};
}

Shelf::~Shelf()
{
	for (size_t i = 0; i < this->used; ++i)
	{
		this->books[i]->removeFromShelf();
	}

	delete[] this->books;
}

bool Shelf::addBook(Book& book)
{
	if (isOnTheShelf(book))
		return false;

	if(this->currentPagesCount + book.getPages() > this->pagesMaxCount)
		return false;

	if (this->used >= this->allocated)
	{
		size_t newCapacity = (this->allocated == 0) ? 1 : 2 * this->allocated;
		
		assert(this->used <= newCapacity);

		Book** temp = new (std::nothrow) Book * [newCapacity] {};
		if (!temp)
			return false;

		for (size_t i = 0; i < this->used; ++i)
		{
			temp[i] = this->books[i];
		}

		delete[] this->books;
		this->books = temp;

		this->allocated = newCapacity;
	}

	assert(this->used <= this->allocated);

	this->books[this->used] = &book;
	++this->used;

	book.setShelf(this);

	this->currentPagesCount += book.getPages();
	return true;
}

const Book* Shelf::at(size_t index) const
{
	if (index >= this->used)
		throw std::out_of_range("Index out of range!");

	return this->books[index];
}

Book* Shelf::at(size_t index)
{
	if (index >= this->used)
		throw std::out_of_range("Index out of range!");

	return this->books[index];
}

bool Shelf::setMaxNumberOfPages(unsigned pagesMaxCount)
{
	if(this->pagesMaxCount > pagesMaxCount)
	{
		int i = (int) this->used - 1;
		while (i >= 0 && this->currentPagesCount > pagesMaxCount)
		{
			if (!this->removeBook(i))
				return false;
		}
	}

	this->pagesMaxCount = pagesMaxCount;
	return true;
}

void Shelf::attachToBookshelf(Bookshelf* bookshelf, size_t position)
{
	this->bookshelf = bookshelf;
	this->position = position;
}

void Shelf::print() const
{
	for (size_t i = 0; i < this->used; ++i)
	{
		this->books[i]->print(std::cout);
		std::cout << "\n";
	}
}

int Shelf::findBook(const char* name) const
{
	if(!name)
		return -1;

	for (size_t i = 0; i < this->used; ++i)
	{
		if (strcmp(name, this->books[i]->getName()) == 0)
			return (int)i;
	}

	return -1;
}

bool Shelf::isOnTheShelf(const Book& book) const
{
	for (size_t i = 0; i < this->used; ++i)
	{
		if (this->books[i] == &book)
			return true;
	}

	return false;
}

bool Shelf::removeBook(const Book& book)
{
	int index = findBook(book.getName());
	if (index < 0)
		return false;

	return this->removeBook(index);
}

bool Shelf::removeBook(size_t index)
{
	if(index >= this->used || !this->books[index])
		return false;

	this->currentPagesCount -= this->books[index]->getPages();

	if (this->books[index]->removeFromShelf())
	{
		for (size_t i = index + 1; i < this->used; ++i)
		{
			this->books[i - 1] = this->books[i];
		}

		this->books[used - 1] = nullptr;
		--this->used;
	}

	return true;
}

