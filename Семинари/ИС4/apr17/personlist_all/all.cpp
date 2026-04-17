
#include <iostream>
#include <new>


struct Date
{
    int year;
    int month;
    int day;
};

bool writeDateText(std::ostream & os, Date const & date);
bool readDateText(std::istream & is, Date & date);

bool writeDateBinary(std::ostream & os, Date const & date);
bool readDateBinary(std::istream & is, Date & date);


struct Person
{
    char name[30];
    char family[30];
    Date birthDate;
};


// data сочи към динамично заделен масив с размер size
// или е nullptr, ако size == 0
struct PersonList
{
    size_t size;
    Person * data;
};


// функциите връщат true при успех и false при грешка
bool personListInit(PersonList & list);
bool personListDestroy(PersonList & list);
bool personListAdd(PersonList & list, Person const & p);
bool personListDelete(PersonList & list, size_t idx);


bool personListPrint(PersonList const & list);


void printDate(Date const & date)
{
    std::cout << date.day << "." << date.month << "." << date.year;
}

bool writeDateText(std::ostream & os, Date const & date)
{
    os << date.day << "." << date.month << "." << date.year;
    return !os.fail();
};

static
void check(std::istream & is, char c)
{
    if(is.peek() == c)
        is.get();
    else
        is.setstate(std::ios::failbit);

}

static
bool isLeap(int year)
{
    if(year % 400 == 0)
        return true;
    if(year % 100 == 0)
        return false;
    if(year % 4  == 0)
        return true;
    return false;
}

bool checkDate(Date const & d)
{
    if(d.month <= 0 || d.month > 12) 
        return false;

    if(d.year == 0)
        return false;

    if(d.day <= 0 || d.day > 31 )
        return false;

    switch(d.month)
    {
        case 4:
        case 6:
        case 9:
        case 11:
            if(d.day > 30)
                return false;
        break;

        case 2:
            if(d.day > 28 + isLeap(d.year))
                return false;
    }

    return true;
}


bool readDateText(std::istream & is, Date & date)
{
    is >> date.day;
    check(is,'.');
    is >> date.month;
    check(is,'.');
    is >> date.year;

    if(!checkDate(date))
        is.setstate(std::ios::failbit);

    return !is.fail();
}


bool writeDateBinary(std::ostream & os, Date const & d)
{
    os.write((char*)&d, sizeof(d));
    return !os.fail();
};

bool readDateBinary(std::istream & is, Date & d)
{
    is.read((char*)&d, sizeof(d));
    return !is.fail();
}


bool personListInit(PersonList & list)
{
    list.size = 0;
    list.data = nullptr;
    return true;
}


bool personListAdd(PersonList & list, Person const & p)
{
    Person * newData = new(std::nothrow) Person[list.size + 1];
    if(newData == nullptr)
        return false;

    for(size_t k = 0; k < list.size; ++k)
        newData[k] = list.data[k];

    newData[list.size] = p;

    delete[] list.data;

    list.size++;
    list.data = newData;


    return true;

}


bool personListDelete(PersonList & list, size_t idx)
{
    if(idx + 1 > list.size)
        return false;

    for(size_t k = idx; k + 1 < list.size; ++k)
    {
        list.data[k] = list.data[k+1];
    }

    list.size--;

    return true;
}



bool personListDestroy(PersonList & list)
{
    delete[] list.data;
    list.size = 0;
    list.data = nullptr;
    
    return true;
}



bool personListPrint(PersonList const & list)
{
    for(size_t k = 0; k < list.size; ++k)
    {
        Person const & p = list.data[k];
        std::cout << k+1 << "." << p.name << " " << p.family << " "
                  << p.birthDate.day << "." << p.birthDate.month << "." << p.birthDate.year
                  << std::endl;
    }
    return std::cout.good();
}

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