#include <cassert>
#include <fstream>
#include <iostream>

#include "DesktopDevice.h"
#include "MobileDevice.h"
#include "Server.h"

int main()
{
    try
    {
        Server server(4, 10);

        MobileDevice m1("gosho", 73);
        MobileDevice m2("tosho", 92);
        MobileDevice m3("losho", 2);
        DesktopDevice d1("Georgi", "www.g.com");
        DesktopDevice d2("Todor", "www.t.bg");
        DesktopDevice d3("Ivan", "www.i.net");

        // Time - 0
        std::cout << "====== Tick 0 ======\n";
        server.Connect(m1);
        server.Connect(d1);
        server.Print();

        // Time - 3
        std::cout << "\n====== Tick 3 ======\n";
        server.Tick(3);
        server.Connect(m2);
        server.Print();
        bool saved = server.SaveLog("server.log");
        assert(saved == true);
        std::cout << " == Saved to server.log == \n";

        // Time - 5
        std::cout << "\n====== Tick 5 ======\n";
        server.Tick(2);
        server.Connect(d2);
        bool wasConnected = server.Connect(m3);
        assert(wasConnected == false);
        server.Print();

        // Time - 11
        std::cout << "\n====== Tick 11 ======\n";
        server.Tick(6);
        server.Disconnect(8);
        server.Connect(m3);
        server.Print();

        std::cout << " == Loaded from server.log == \n";
        Server loadedServer(4, 10);
        loadedServer.LoadLog("server.log");
        loadedServer.Print();

        saved = loadedServer.SaveLog("server.log");
        assert(saved == true);
        std::cout << " == Saved to server.log == \n";

        std::cout << "\n ====== Last log ======\n";
        std::ifstream file("server.log");
        char ch;
        while (file.get(ch))
            std::cout << ch;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "An exception occurred: " << ex.what() << "\n";
        std::cerr << "Terminating...";
    }

    return 0;
}
