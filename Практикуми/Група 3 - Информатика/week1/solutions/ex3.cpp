#include <iostream>

int countDelitels (int n) {
    if (n < 0) {
        n*=-1;
    }
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            ++count;
        }
    }
    return count;
}

bool isPrime(int n) {
    return countDelitels(n) == 2;
}

int main(){
    int n;
    std::cin >> n;
    std::cout << countDelitels(n) << " " << isPrime(n) << std::endl;
    return 0;
}
