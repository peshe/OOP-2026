#include <iostream>
#include <string>
using namespace std;

template<typename T, typename U>
struct Pair {
    T first;
    U second;
};

template<typename T>
void swap(Pair<T, T>& p) {
    T tmp = p.first;
    p.first = p.second;
    p.second = tmp;
}

template<typename T, typename U>
void print(const Pair<T, U>& p) {
    cout << "(" << p.first << ", " << p.second << ")\n";
}

int main() {
    Pair<int, double> p1 = {3, 4.5};
    print(p1);

    Pair<int, int> p2 = {10, 20};
    swap(p2);
    print(p2);

    Pair<string, char> p3 = {"hello", 'A'};
    print(p3);

    return 0;
}
