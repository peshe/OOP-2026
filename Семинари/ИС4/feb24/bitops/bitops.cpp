#include <iostream>



// променя бита на позиция bit в единица
void setbit(int & a, size_t bit)
{
    a |= (1 << bit);
}

// променя бита на позиция bit в нула
void clearbit(int & a, size_t bit)
{ 
    a &= ~(1 << bit);
}

// връща стойността на бита на позиция bit
// 0->false, 1->true
bool tesbit(int const & a, size_t bit)
{
    return 0 != (a & (1 << bit));
}

// за домашно - да се изведе n в двоичен вид
void printbits(int n)
{

}

int main()
{
    int a = 6, b  = 8;

    std::cout << (a & b) << std::endl;
}
