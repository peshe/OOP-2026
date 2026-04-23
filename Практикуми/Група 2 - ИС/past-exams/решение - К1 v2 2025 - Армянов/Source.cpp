#include "Appliance.h"
#include "Socket.h"

#include <fstream>

int main()
{
    unsigned N;
    double I;

    std::cin >> N >> I;
    if (N == 0 || I <= 0) 
        return 1;
    
    while (std::cin && std::cin.peek() != '\n')
        std::cin.get();
    std::cin.get();

    Appliance* apps;
    try {
        apps = new Appliance[N + 1];
    }
    catch (...) {
        return 2;
    }

    char fileName[1024];
    std::cin.getline(fileName, sizeof(fileName));
    
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "The file was not opened!\n";
        return 1;
    }

    unsigned current = 0;
    while (file && current <= N) {
        try {
            if (apps[current].read(file))
                ++current;
        }
        catch (...) {
            ;
        }
    }
    file.close();

    while (current <= N) {
        try {
            apps[current] = apps[0];
            ++current;
        }
        catch (...) {
            ;
        }
    }

    try {
        Socket s(N, I);
        for (unsigned i = 0; i < N; ++i)
            s.plugIn(apps + i);

        if (s.plugIn(apps + N)) {
            std::cout << "Added more device than sockets\n";
        }
        s.print();

        for (unsigned i = 0; i < N; ++i) {
            apps[i].turnOn();
            if (s.isDown()) {
                std::cout << "The socket is down!\n";
            }
        }
        s.print();
    }
    catch (...) {
        ;
    }

    delete[] apps;
    return 0;
}
