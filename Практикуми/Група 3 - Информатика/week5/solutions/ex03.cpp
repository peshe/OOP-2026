#include <iostream>
using namespace std;


using bit_count_type = short unsigned int;

struct BitStats {
    bit_count_type ones;
    bit_count_type zeros;
    bit_count_type msb;
};


template<typename T>
bit_count_type countBits(T value) {
    bit_count_type count = 0;
    for (size_t i = 0; i < sizeof(T) * 8; i++) {
        if ((value >> i) & T(1))
            count++;
    }
    return count;
}

template<typename T>
BitStats analyze(T value) {
    bit_count_type total = sizeof(T) * 8;
    bit_count_type ones = (bit_count_type)countBits(value);
    bit_count_type msb = (bit_count_type)-1;
    for (bit_count_type i = total - 1; i >= 0; i--) {
        if ((value >> i) & T(1)) {
            msb = i;
            break;
        }
    }
    return {ones, total - ones, msb};
}

int main() {
    unsigned char v = 0b10110101;
    BitStats s = analyze(v);
    cout << "Стойност:  " << (int)v << " (0b10110101)\n";
    cout << "Единици:   " << s.ones  << "\n";
    cout << "Нули:      " << s.zeros << "\n";
    cout << "MSB поз.:  " << s.msb   << "\n\n";

    unsigned int u = 0xDEADBEEF;
    BitStats s2 = analyze(u);
    cout << "0xDEADBEEF — единици: " << s2.ones << ", MSB: " << s2.msb << "\n";

    return 0;
}
