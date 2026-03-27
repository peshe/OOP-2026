#include <iostream>
#include <cmath>
using namespace std;

template<typename T, size_t N = 2>
struct Point {
    T coords[N];

};

template<typename T, size_t N = 2>
T dot(const Point<T, N>& left, const Point<T, N>& right) {
    T result = T(0);
    for (size_t i = 0; i < N; i++)
        result += left.coords[i] * right.coords[i];
    return result;
}

template<typename T, size_t N>
void add(const Point<T, N>& a, const Point<T, N>& b, Point<T, N>& out) {
    for (size_t i = 0; i < N; i++)
        out.coords[i] = a.coords[i] + b.coords[i];
}

template<typename T, size_t N>
void sub(const Point<T, N>& a, const Point<T, N>& b, Point<T, N>& out) {
    for (size_t i = 0; i < N; i++)
        out.coords[i] = a.coords[i] - b.coords[i];
}

template<typename T, size_t N>
double norm(const Point<T, N>& p) {
    return sqrt((double)dot(p, p));
}


template<typename T, size_t N>
double norm2(const Point<T, N>& p) {
    T sum = T(0);
    for (size_t i = 0; i < N; i++)
        sum += abs(p.coords[i]);
    return sum;
}

template<typename T, size_t N>
double norm3(const Point<T, N>& p) {
    // Чебишова или равномерна норма
    // Ще я ползвате по ЧМ/ЧА.
    T max = abs(p.coords[0]);
    for (size_t i = 1; i < N; i++) {
        T val = (p.coords[i] > max)?abs(p.coords[i]):max;
    }
    return max;
}

template<typename T, size_t N>
void print(const Point<T, N>& p) {
    cout << "(";
    for (size_t i = 0; i < N-1; i++) {
        cout << p.coords[i] << ", ";
    }
    cout << p.coords[N-1] << ")";
}

int main() {
    Point<double, 3> a = {1.0, 2.0, 3.0};
    Point<double, 3> b = {4.0, 5.0, 6.0};
    Point<double, 3> c;

    add(a, b, c);
    cout << "a + b = "; print(c); cout << "\n";

    sub(b, a, c);
    cout << "b - a = "; print(c); cout << "\n";

    cout << "Скаларно произведение: " << dot(a, b) << "\n";
    cout << "Норма на a: " << norm(a) << "\n";

    return 0;
}
