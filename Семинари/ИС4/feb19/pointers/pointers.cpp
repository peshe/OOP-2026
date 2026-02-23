#include <iostream>

// Предаване на масив по reference
void g(int (&a)[5])
{
     a[1] = 44;
}

// Предаване на променлива по reference
void g(int & a)
{
    a = 42;
}

// Предаване на указтел
void g(int * a)
{
    *a = 43;
}


// Предаване на указател
void f(int *a)
{
    a[20] = 20;
}


void h()
{

    int a = 6;

    const int * p1 = &a;
    int const * p2 = &a;
    int * const p3 = &a;
    
    

}

int main()
{
    int a = 6, b = 8;

    int * pa = &a;
    int * pb = &b;

    pa = pb;


    int arr[] = {1,2,3};
    int arr2[] = {1,2,3,4,5};

    // parr сочи към първият елемент на arr
    int * parr = arr;

    

    // std::cout << a << " " << b << std::endl;
    // std::cout << sizeof(arr) << " " << sizeof(parr) << std::endl;

    
    // променя се първият елемент на масива
    g(&arr[0]);

    // същото
    // g(int(&)[5]) не се вика, защото масивът
    // е с 3 елемена
    g(arr);

    // грешка - нееднозначност между
    // g(int*)
    // и
    // g(int(&)[5])
    g(arr2);

    // променя се вторият елемент на масива
    g(&arr[1]);

    // същото, но с аритметика с указатели
    g(arr+1);
    

    std::cout << arr[1] << std::endl;

}