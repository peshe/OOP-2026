#include <iostream>
#include <cstdint>
using namespace std;

template<typename T>
struct BitMask {
    T val;
};

template<typename T>
void set(BitMask<T>& m, int pos) { m.val |=  (T(1) << pos); }

template<typename T>
void clear(BitMask<T>& m, int pos) { m.val &= ~(T(1) << pos); }

template<typename T>
void toggle(BitMask<T>& m, int pos) { m.val ^=  (T(1) << pos); }

template<typename T>
bool test(const BitMask<T>& m, int pos) { return (m.val >> pos) & T(1); }

template<typename T>
T value(const BitMask<T>& m) { return m.val; }

template<typename T>
BitMask<T> merge(BitMask<T> a, BitMask<T> b, T mask) {
    return {(a.val & mask) | (b.val & ~mask)};
}

int main() {
    BitMask<uint8_t> m = {0};
    set(m, 0);
    set(m, 3);
    set(m, 7);
    cout << "След set(0,3,7): " << (int)value(m) << " (очаквано 137)\n";

    toggle(m, 3);
    cout << "След toggle(3):  " << (int)value(m) << " (очаквано 129 = 137-2^3=137-8)\n";

    cout << "Бит 7 е: " << test(m, 7) << "\n";
    cout << "Бит 3 е: " << test(m, 3) << "\n";

    BitMask<uint8_t> a = {uint8_t(0b11110000)};
    BitMask<uint8_t> b = {uint8_t(0b00001111)};
    uint8_t mask = 0b11000011;

    auto merged = merge(a, b, mask);
    cout << "Merge: " << (int)value(merged) << " (очаквано 204 = 0b11001100)\n";

    return 0;
}
