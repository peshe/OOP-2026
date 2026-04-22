#pragma once

#include "Book.h"
#include "Shelf.h"

class Bookshelf
{
public:
	Bookshelf(unsigned countShelves, unsigned pagesMaxCount);
	Bookshelf(const Bookshelf& other) = delete;
	Bookshelf& operator=(const Bookshelf& other) = delete;
	~Bookshelf();

	const Book* findBook(const char* name) const;

	bool addBook(Book& book);
	bool removeBook(const Book& book);

	bool changeShelvesSize(unsigned newSize);

	void print() const;

private:
	const unsigned numberOfShelves;
	Shelf* shelves;
};