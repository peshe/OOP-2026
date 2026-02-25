#include <iostream>


enum Class{
    Goblin = 1,
    Giant = 2,
    Ork = 4,
    Human = 8,
    Wolfosaurus = 16,
    Orangelion = 32,
    Bloodystrawbery = 64
};
int generateBasedOnId(const int id) {
    srand(id);
    return rand() % 126 + 1;
}
void printRace(int index) {
    switch (index)
    {
    case Goblin:
        std::cout << "Goblin" << std::endl;
        break;
    case Giant:
        std::cout << "Giant" << std::endl;
        break;
    case Ork:
        std::cout << "Ork" << std::endl;
        break;
    case Human:
        std::cout << "Human" << std::endl;
        break;
    case Wolfosaurus:
        std::cout << "Wolfosaurus" << std::endl;
        break;
    case Orangelion:
        std::cout << "Orangelion" << std::endl;
        break;
    case Bloodystrawbery:
        std::cout << "Bloodystrawbery" << std::endl;
        break;
    default:
        std::cout << "Invalid race check your code" << std::endl;
        break;
    }
}

void printFullDNA(int index) {
    for (int i = 0; i < 7; ++i) {
        int bitmask = (1 << i);
        if (index & bitmask) {
            printRace(bitmask);
        }
    }
}

int main() {
    int id;
    std::cin >> id;
    int dna = generateBasedOnId(id);
    printFullDNA(dna);
    return 0;
}
