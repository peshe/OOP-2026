#include <iostream>
#include <fstream>

#include "Book.h"
#include "Shelf.h"
#include "Bookshelf.h"

int main()
{
	unsigned n, m;
	std::cin >> n >> m;

	if (!std::cin || n == 0 || m == 0)
		return 1;

	Book* books = nullptr;

	try
	{
		Bookshelf bs(n, m);

		std::ifstream file("Books.txt", std::ios::in);
		if (!file)
		{
			std::cerr << "The file cannot be opened!\n";
			return 1;
		}

		unsigned count;
		file >> count;
		if (!file)
		{
			std::cerr << "Wrong data format!\n";
			return 1;
		}

		books = new Book[count];
		size_t i = 0;

		while (file.good())
		{
			if (books[i].read(file))
			{
				books[i].print();

				if (bs.addBook(books[i]))
				{
					std::cout << "The book was put on the shelf!\n";
				}
				else
				{
					std::cout << "The book wasn't put on the shelf!\n";
				}

				++i;
			}
		}

		const Book* ontheShelf = bs.findBook("Wound");
		if (ontheShelf)
		{
			std::cout << "The book is on the shelf!\n";
			bs.removeBook(*ontheShelf);

			bs.print();
		}

		delete[] books;
	}
	catch (...)
	{
		delete[] books;
		std::cerr << "Exception has occurred!\n";
	}
}