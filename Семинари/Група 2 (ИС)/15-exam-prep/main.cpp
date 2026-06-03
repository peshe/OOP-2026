#include <iostream>

#include "AlternateDataSource.h"
#include "ArrayDataSource.h"
#include "DefaultDataSource.h"
#include "FileDataSource.h"
#include "GeneratorDataSource.h"

//struct Test
//{
//    int a = 42;
//
//    Test(int a = 0) : a(a) {}
//    operator int() const { return a; }
//};

int main()
{
    //DefaultDataSource<int> defaultDataSource;
    ////for (Test num : dataSource.GetMultiple(5))
    ////    std::cout << num.a << std::endl;
    ////
    ////Test test;
    ////dataSource >> test;
    ////std::cout << test;
    //
    //FileDataSource<int> fileDataSource("ints.txt");
    ////while (fileDataSource.HasNext())
    ////    std::cout << fileDataSource.Get() << " ";
    //
    //ArrayDataSource<int> arrayDataSource({1, 2, 3});
    //
    //AlternateDataSource<int> alternateDataSource =
    //    AlternateDataSource<int>::TakeSources({ new DefaultDataSource(defaultDataSource),
    //                                            new FileDataSource(fileDataSource),
    //                                            new ArrayDataSource(arrayDataSource)});
    //
    //for (int elem : alternateDataSource.GetMultiple(3))
    //    std::cout << elem << "\n";
    //
    //AlternateDataSource<int> copySrc = alternateDataSource;
    //for (int elem : copySrc.GetMultiple(20))
    //    std::cout << elem << "\n";
    //
    //for (int elem : alternateDataSource.GetMultiple(3))
    //    std::cout << elem << "\n";
    //
    //alternateDataSource.Reset();
    //
    //for (int elem : alternateDataSource.GetMultiple(3))
    //    std::cout << elem << "\n";

    using GeneratorFn = int();
    GeneratorDataSource<int, GeneratorFn*> randGenerator(rand);

    //struct Generator2
    //{
    //    int operator()() const { return 32; }
    //};
    //GeneratorDataSource<int, Generator2> gen32(Generator2{});
    //
    //srand(time(nullptr));
    //for (int elem : randGenerator.GetMultiple(10))
    //    std::cout << elem << "\n";

    struct NaturalNumGenerator
    {
        int num = 0;
        int operator()() { return num++; }
    };

    struct FibGenerator
    {
        int fib1 = 0;
        int fib2 = 1;

        int operator()()
        {
            int temp = fib1;
            fib1 = fib2;
            fib2 += temp;
            return fib1;
        }
    };

    FibGenerator fibGen;
    std::vector<int> fib;
    for (int i = 0; i < 25; i++)
        fib.push_back(fibGen());


    AlternateDataSource<int> altSrc({ new GeneratorDataSource<int, NaturalNumGenerator>({}),
                                      new GeneratorDataSource(randGenerator),
                                      new ArrayDataSource(fib) });

    //for (int elem : altSrc.GetMultiple(1000))
    //    std::cout << elem << "\n";

    struct RandStrGenerator
    {
        std::string operator()()
        {
            std::string str(10, ' ');
            for (int i = 0; i < 10; i++)
                str[i] = 'a' + rand() % 26;
            return str;
        }
    };

    GeneratorDataSource<std::string, RandStrGenerator> gen({});
    for (int i = 0; i < 50; i++)
        std::cout << gen.Get() << "\n";

    return 0;
}
