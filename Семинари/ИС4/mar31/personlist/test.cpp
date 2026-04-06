#include "date.h"
#include "personList.h"

// включваме масива с тестови данни
// #include "somePeople.inl"

#include <fstream>

void test1()
{
    std::fstream fs;

    fs.open("dates.txt", std::ios::in);

    Date d1,d2;

    bool b1 = readDateText(fs, d1);
    bool b2 = readDateText(fs, d2);

    if(b1) writeDateText(std::cout, d1);
    std::cout << std::endl;
    if(b2) writeDateText(std::cout, d2);

}

void test2()
{

    std::fstream bfs;
    bfs.open("dates.bin", std::ios::binary | std::ios::out );
    bfs.seekp(0);

    Date d1 {1980,02,13};
    writeDateBinary(bfs, d1);

    bfs.close();
    bfs.open("dates.bin", std::ios::binary | std::ios::in );

    Date d3;
    bfs.seekg(0);
    readDateBinary(bfs, d3);

    writeDateText(std::cout, d3);


}

int main()
{
    // test1();
    test2();

    
}