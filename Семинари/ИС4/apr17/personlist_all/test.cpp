#include "date.h"
#include "person.h"
#include "person_list.h"

#include <fstream>

void test1()
{
    std::cout << "====" << __FUNCTION__ << "====" << std::endl;
    std::fstream fs;

    fs.open("dates.txt", std::ios::in);

    Date d1,d2;

    fs >> d1 >> d2;

    std::cout << d1;
    std::cout << std::endl;
    std::cout << d2;

}

void test2()
{

    std::cout << "====" << __FUNCTION__ << "====" << std::endl;

    std::fstream bfs;
    bfs.open("dates.bin", std::ios::binary | std::ios::out );
    bfs.seekp(0);

    Date d1 {1980,02,13};
    d1.write(bfs);

    bfs.close();
    bfs.open("dates.bin", std::ios::binary | std::ios::in );

    Date d3;
    bfs.seekg(0);
    d3.read(bfs);

    std::cout << d3;

}

void test3()
{

    std::cout << "====" << __FUNCTION__ << "====" << std::endl;

    Person p1 { "Иван", "Петров", Date {1970,1,1}};

    std::cout << p1;


}

#include "somePeople.inl"

void test4()
{

    std::cout << "====" << __FUNCTION__ << "====" << std::endl;

    PersonList list;
    list.append(somePeople[2]);
    list.append(somePeople[3]);

    PersonList list2(list);
    PersonList list3;
    list3 = list2;

    std::cout << list << std::endl;
    std::cout << list2 << std::endl;
    std::cout << list3 << std::endl;

}


void test5()
{

    std::cout << "====" << __FUNCTION__ << "====" << std::endl;

    PersonList list;
    list.append(somePeople[4]);
    list.append(somePeople[5]);

    std::cout << list << std::endl;

    list.erase(0);

    std::cout << list << std::endl;
}
int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();    
}