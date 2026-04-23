#pragma once

#include <iostream>

class Shelf;

class Book
{
	friend class Shelf;

public:
	Book(const char* name = "Unknown", const char* author = "Unknown", unsigned pages = 0);
	Book(const Book& other);
	Book(Book&& other) noexcept;
	Book& operator=(const Book& other);
	Book& operator=(Book&& other) noexcept;
	~Book() noexcept;

	const char* getName() const { return this->name; }
	const char* getAuthor() const { return this->author; }
	const char* getID() const { return this->id; }
	unsigned getPages() const { return this->pages; }

	void setName(const char* newName);
	void setAuthor(const char* newAuthor);

	bool print(std::ostream& out = std::cout) const;
	bool read(std::istream& in);

	bool isOnShelf(const Shelf& shelf) const;
	bool putOnShelf(Shelf& shelf);
	bool removeFromShelf();

private:
	void setShelf(Shelf* shelf) { this->shelf = shelf; }

private:
	static bool isValid(const char* str);
	static void setNextID(char* str);
	static void copy(char*& destination, const char* source);

	static bool clearContent(std::istream& in, char delim = '\n');
	static char* readString(std::istream& in);

private:
	static unsigned nextID;
	static unsigned count;
	static const unsigned MAX_COUNT = 500;

private:
	char* name;
	char* author;
	unsigned pages;
	char id[12];

	Shelf* shelf;
};