#include "personList.h"

// включваме масива с тестови данни
#include "somePeople.inl"

#include <iostream>

int main()
{
    PersonList list;

    std::cout << "====" << std::endl;

    personListInit(list);
    personListPrint(list);

    std::cout << "====" << std::endl;

    bool ok = personListDelete(list, 2);
    std::cout << ok << std::endl;


    std::cout << "====" << std::endl;

    for(size_t k = 0; k < 5; ++k)
    {
        personListAdd(list, somePeople[k]);
    }

    personListPrint(list);


    std::cout << "====" << std::endl;

    ok = personListDelete(list, 2);

    std::cout << ok << std::endl;
    personListPrint(list);

    std::cout << "====" << std::endl;


    for(size_t k = 5; k < somePeopleCount; ++k)
    {
        personListAdd(list, somePeople[k]);
    }

    personListPrint(list);
}