#define _CRT_SECURE_NO_WARNINGS

#include "Utils.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

char* copy(const char* str)
{
	if (!str || !*str)
		throw std::invalid_argument("Error: empty string!");

    char* temp = new char[strlen(str) + 1];

    strcpy(temp, str);
    return temp;
}

char* readString(std::istream& is, char delimiter)
{
	if (!is) return nullptr;

	size_t capacity = 128;
	char* buffer = new (std::nothrow) char[capacity];

	int size = 0;
	if (!buffer) return nullptr;

	char symbol = 0;
	while (is.get(symbol) && symbol != delimiter)
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

void skipWhiteSpaces(std::istream& is)
{
	char c;
	while (is.get(c) && isspace(c));
	
	if (is)
		is.putback(c);
}

