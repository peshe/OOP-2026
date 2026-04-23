#pragma once

#include "Book.h"

class Bookshelf;

class Shelf
{
public:
	Shelf(unsigned pagesMaxCount = 1000);
	Shelf(const Shelf& other) = delete;
	Shelf& operator=(const Shelf& other) = delete;
	~Shelf();

	bool addBook(Book& book);

	int findBook(const char* name) const;

	bool removeBook(const Book& book);
	bool removeBook(size_t index);
	
	const Book* at(size_t index) const;
	Book* at(size_t index);

	size_t getNumberOfBooks() const { return this->used; }

	unsigned getMaxNumberOfPages() const { return this->pagesMaxCount; }
	bool setMaxNumberOfPages(unsigned pagesMaxCount);

	void attachToBookshelf(Bookshelf* bookshelf, size_t position);
	size_t getPosition() const { return this->position; }

	void print() const;

private:
	bool isOnTheShelf(const Book& book) const;

private:
	Bookshelf* bookshelf;
	size_t position;

	Book** books;
	size_t used;
	size_t allocated;

	unsigned currentPagesCount;
	unsigned pagesMaxCount;
};