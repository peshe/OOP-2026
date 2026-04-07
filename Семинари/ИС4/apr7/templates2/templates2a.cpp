// templates2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "arrayList.h"
#include "person.h"

#include "somePeople.inl"

#include <new>
#include <iostream>

std::ostream& operator << (std::ostream& os, Person p)
{
	os << p.name << std::endl << p.family << std::endl << p.birthDate.year << "." << p.birthDate.month << "." << p.birthDate.day;
	return os;
}

int main()
{
	ArrayList<Person> list;

	arrayListAdd(list, somePeople[2]);
	arrayListAdd(list, somePeople[4]);
	arrayListAdd(list, somePeople[6]);

	arrayListPrint(list);

	arrayListDestroy(list);

}