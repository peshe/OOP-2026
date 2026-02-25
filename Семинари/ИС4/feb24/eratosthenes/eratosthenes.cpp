#include <cstddef>
#include <stdexcept>
#include <iostream>

// връща позицията на първата намерена стойност false в а
size_t first_false(bool * a, size_t n)
{
    for(size_t i = 0; i < n; ++i)
        if(false == a[i])
            return i;

    return 0;
}


// проверка дали числото n е просто по метода на Ератостен
bool eratosthenes(size_t n)
{
    n++;

    // s[k] == true -> k e зачеркнато
    bool *s = new bool[n];
    for(size_t i = 0; i<n; ++i)
        s[i] = false;
    
    s[0]=s[1]=true;
    size_t base = 0;
    bool rtn = false;

    // безкраен цикъл
    while(true)
    {
        // за да търсим в края на s използваме аритметика с указатели
        // като начало се предава s+base+1, a броят на елементи
        // до края е n - base -1
        // намерената позиция се събира с base + 1 за да получим
        // неотместен индекс на първото незачеркнато число
        base = base + 1 + first_false(s + base + 1,n - base - 1);

        if (0 == base)
        {
            rtn = false;
            break;
        }

        if (base * base > n)
        {
            rtn = (s[n-1] == false);
            break;
        }

        for(size_t k = base + base; k < n; k+=base)
            s[k] = true;

    };

    delete[] s;
    return rtn;

}

int main()
{
    std::cout << (eratosthenes(17)?"TRUE":"FALSE") << std::endl;
}