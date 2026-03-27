#include <iostream>
using namespace std;

template<typename T, size_t N = 10>
struct Array {
    T data[N];
};

template<typename T, size_t N = 10>
bool at(Array<T, N>& arr, size_t index, T& out) {
    if (index >= N) return false;
    out = arr.data[index];
    return true;
}

template<typename T, size_t N = 10>
size_t size(const Array<T, N>&) {
    return N;
}

template<typename T, size_t N = 10>
Array<T, N> fill(const T& value) {
    Array<T, N> arr;
    for (size_t i = 0; i < N; i++)
        arr.data[i] = value;
    return arr;
}

int main() {
    auto arr = fill<int, 5>(7);

    int val;
    for (size_t i = 0; i < size(arr); i++) {
        if (at(arr, i, val))
            cout << val << " ";
    }
    cout << "\n";

    if (!at(arr, 10, val))
        cout << "Грешка: индекс извън граници\n";

    auto darr = fill<double>(3.14);
    double d;
    at(darr, 1, d);
    cout << "darr[1] = " << d << "\n";
    cout << "Размер на darr: " << size(darr) << "\n";

    return 0;
}
