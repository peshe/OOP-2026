
#include <iostream>

struct Date
{
    int year;
    int month;
    int day;
};

using std::cin;
using std::cout;
using std::endl;

void readDate(Date & d)
{
    cin >> d.year >> d.month >> d.day;
}


bool checkDate(Date d)
{
    if(month <= 0 || month > 12) 
        return false;

    if(year == 0)
        return false;

    if(day <=0 || day > 31)
        return false;

    switch(month)
    {
        case 2:
            if(day > 28 + (year % 4 == 0))
                return false;   
        break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(day > 30)
                return false;
        break;
    }
}


bool compareDates(Date a, Date b)
{
    if(b.year > a.year)
        return true;
    else if(b.year == a.year && b.month > a.month)
        return true;
    else if(b.year == a.year && b.month == a.month && b.day > a.day)
        return true;
    else
        return false;
}


struct Person
{
    char name[30];
    char family[30];
    Date birthDate;
};

void readPeson(Person & p)
{
    cin >> name >> family;
    readDate(p.birthDate);
}


int oldestPeson(Person persons[], size_t n)
{
    
}



int main()
{
    Date d;

    readDate(d);

    cout << (&d.month - &d.year) << endl;
    cout << sizeof(d.month) << endl;

    Date a,b;
    a = b;
}