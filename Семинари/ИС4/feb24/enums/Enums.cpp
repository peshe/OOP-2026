// Enums.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


//using Gender = int;


enum Gender
{
    GENDER_M,
    GENDER_F,
    //GENDER_OTHER
};


// ако имаме повече стойности за Gender от
// случаите в switch, някои компилатори дават
// предупреждение
void printGender(Gender g)
{
    switch (g)
    {
    case GENDER_M: 
        std::cout << "Male"; 
        break;
    case GENDER_F: 
        std::cout << "Female"; 
        break;
    }
}

int main()
{
    Gender a = GENDER_M;
    printGender(a);
}

