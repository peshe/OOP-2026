#include <iostream>
#include <vector>

int main()
{
    // STL

    //int* temp = new int[2];
    //temp[0] = 42;
    //temp[1] = 98;
    //std::cout << temp[100000] << "\n";

    std::vector<int> arr;
    arr.push_back(42);
    arr.push_back(98);

    std::cout << arr[0] << "\n";
    std::cout << arr[1] << "\n";
    std::cout << arr[2] << "\n";

    std::cout << arr.at(0) << "\n";
    std::cout << arr.at(1) << "\n";
    //std::cout << arr.at(2) << "\n";

    arr.shrink_to_fit();

    class Person
    {
    public:
        Person() = default;
        Person(const std::string& name) : name(name) {}

    private:
        std::string name;
    };

    std::vector arr2(20, Person("Tosho"));

    arr2.resize(10, Person("georgi"));
    arr2.reserve(1000);

    //if (idx < arr.size())

    arr.pop_back();
    arr.clear();

    //if (arr.empty())

    std::string str = "gosho";

    std::cout << str;
    str.push_back('a');
    str.append("fmi");
    str += "gosho";
    str.clear();
    //if (str.empty())

    std::array<int, 10> arr3;  // default constructs the ints
    int arr4[10];

    return 0;
}