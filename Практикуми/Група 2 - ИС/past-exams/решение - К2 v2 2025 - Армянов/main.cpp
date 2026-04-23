#include <iostream>

#include "Calendar.h"

int main()
{
	try
	{
		Calendar may(5);

		Event event;
		std::cin >> event;
		may += event;

		Meeting meating;
		std::cin >> meating;
		may += meating;

		Task task;
		std::cin >> task;
		may += task;

		Task anotherTask("Exam", "OOP exam", 4, false, Date{ 12, 6 });
		may += anotherTask;

		++may;

		std::cout << may << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout
			<< "Exception has occurred!\n"
			<< ex.what() << std::endl;
	}

	return 0;
}