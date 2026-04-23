#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"
#include "Shelf.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <utility>

unsigned Book::nextID = 0;
unsigned Book::count = 0;

Book::Book(const char* name, const char* author, unsigned pages)
	: name(nullptr), author(nullptr), pages(pages), shelf(nullptr) 
{
	if (count > Book::MAX_COUNT)
		throw std::logic_error("Maximum number of books has been reached!");

	setNextID(this->id);

	try
	{
		this->setName(name);
		this->setAuthor(author);
	}
	catch (std::exception&)
	{
		delete[] this->name;
		delete[] this->author;

		throw;
	}

	++count;
}

Book::Book(const Book& other)
	: Book(other.name, other.author, other.pages)
{}

Book::Book(Book&& other) noexcept
	: name(nullptr), author(nullptr), pages(other.pages), shelf(nullptr)
{
	setNextID(this->id);

	std::swap(this->name, other.name);
	std::swap(this->author, other.author);

	++count;
}

Book& Book::operator=(const Book & other)
{
	if (this != &other)
	{
		// копирането може да създаде проблем,
		// ako надвишим максималния брой живи обекти
		//Book temp(other);
		//*this = std::move(temp);

		char* tempName = nullptr; 
		char* tempAuthor = nullptr;

		try
		{
			copy(tempName, other.name);
			copy(tempAuthor, other.author);
		}
		catch (...)
		{
			delete[] tempName;
			throw;
		}

		// id остава същото

		delete[] this->name;
		this->name = tempName;

		delete[] this->author;
		this->author = tempAuthor;

		this->pages = other.pages;

		if (shelf)
			this->shelf->removeBook(*this);
	}

	return *this;
}

Book& Book::operator=(Book&& other) noexcept
{
	if (this != &other)
	{
		std::swap(this->name, other.name);
		std::swap(this->author, other.author);
		this->pages = other.pages;

		if(shelf)
			this->shelf->removeBook(*this);
	}

	return *this;
}

Book::~Book() noexcept
{
	delete[] this->name;
	delete[] this->author;

	if (this->shelf)
		this->shelf->removeBook(*this);

	--count;
}

void Book::setName(const char* newName)
{
	if (!isValid(newName))
		throw std::invalid_argument("Invalid name!");

	copy(this->name, newName);
}

void Book::setAuthor(const char* newAuthor)
{
	if (!isValid(newAuthor))
		throw std::invalid_argument("Invalid author!");

	return copy(this->author, newAuthor);
}

bool Book::print(std::ostream& out) const
{
	if(!out)
		return false;

	out
		<< this->id << "\t" << this->name << "\t"
		<< this->author << "\t" << this->pages << std::endl;

	if (this->shelf)
	{
		size_t shelfNumber = this->shelf->getPosition();
		int positionOnShelf = this->shelf->findBook(this->name);

		assert(positionOnShelf >= 0);

		out
			<< "The book is on shelf #" << shelfNumber
			<< ", position #" << positionOnShelf << std::endl;
	}

	return out.good();
}

bool Book::read(std::istream& in)
{
	if(!in)
		return false;

	// Не променя ID-то на обекта, в който четем
	char id[12];
	in.getline(id, sizeof(id), '\t');
	if (!in)
		return false;

	char* tempName = readString(in);
	char* tempAuthor = readString(in);

	unsigned tempPages;
	in >> tempPages;

	if (!in || !isValid(tempName) || !isValid(tempAuthor))
	{
		in.clear();
		clearContent(in);

		delete[] tempName;
		delete[] tempAuthor;

		return false;
	}

	delete[] this->name;
	this->name = tempName;

	delete[] this->author;
	this->author = tempAuthor;

	this->pages = tempPages;

	return true;
}

bool Book::isOnShelf(const Shelf& shelf) const
{
	return this->shelf == &shelf;
}

bool Book::putOnShelf(Shelf& shelf)
{
	if(this->shelf && this->shelf == &shelf)
		return false;

	if (this->shelf)
	{
		// this->shelf != &shelf
		this->shelf->removeBook(*this);
	}
	
	this->shelf = &shelf;
	if (!shelf.addBook(*this))
	{
		this->shelf = nullptr;
		return false;
	}

	return true;
}

bool Book::removeFromShelf()
{
	if(!this->shelf)
		return false;

	Shelf* shelf = this->shelf;

	this->shelf = nullptr;
	shelf->removeBook(*this);
	return true;
}

bool Book::isValid(const char* str)
{
	return str && *str;
}

void Book::setNextID(char* id)
{
	const char* pattern = "IS-INF-0000";
	strcpy(id, pattern);

	++nextID;
	
	size_t index = 11;
	id[index] = '\0';

	unsigned copy = nextID;
	while (copy)
	{
		--index;
		id[index] = copy % 10 + '0';
		copy = copy / 10;
	}
}

void Book::copy(char*& destination, const char* source)
{
	assert(source);

	char* temp = new char[strlen(source) + 1];
	strcpy(temp, source);

	delete[] destination;
	destination = temp;
}

bool Book::clearContent(std::istream& in, char delim)
{
	char c;
	while (in.get(c) && c != delim);

	return in.good();
}

char* Book::readString(std::istream& is)
{
	if (!is) return nullptr;

	size_t capacity = 128;
	char* buffer = new (std::nothrow) char[capacity];
	
	int size = 0;
	if (!buffer) return nullptr;
	
	char symbol = 0;
	while (is.get(symbol) && symbol != '\t') 
	{
		if (size == capacity - 1) 
		{
			buffer[size] = '\0';

			capacity *= 2;
			char* newBuffer = new (std::nothrow) char[capacity];
			if (!newBuffer) 
			{
				delete[] buffer;
				return nullptr;
			}

			strcpy(newBuffer, buffer);

			delete[] buffer;
			buffer = newBuffer;
		}

		buffer[size++] = symbol;
	}

	buffer[size] = '\0';
	
	return buffer;
}

