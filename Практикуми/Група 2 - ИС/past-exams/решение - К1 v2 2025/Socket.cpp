#include "Socket.h"
#include "Appliance.h"

Socket::Socket(unsigned slots, double power)
    : slots(slots)
{
    if (power < 0) 
        throw std::invalid_argument("Socket power must be positive");
	
    maxPower = power;
    sockets = new Appliance * [slots];
    for (unsigned i = 0; i < slots; ++i) {
        sockets[i] = nullptr;
    }
}

Socket::Socket(const Socket& s)
    : slots(s.slots)
    , maxPower(s.maxPower)
{
    sockets = new Appliance * [slots];
    for (unsigned i = 0; i < slots; ++i) {
        sockets[i] = nullptr;
    }
}

Socket::~Socket()noexcept
{
    unplugAll();
    delete[] sockets;
}

Socket& Socket::operator=(const Socket& s)
{
    if (&s != this) {
        if (s.slots > slots) {
            throw std::invalid_argument("Incompatible assignment");
        }
        unplugAll();
        maxPower = s.maxPower;
    }
    return *this;
}

bool Socket::plugIn(Appliance* app)
{
    if (isDown()) return false;
    if (!app || app->isPluggedIn()) return false;

    for (unsigned i = 0; i < slots; ++i) {
        if (!sockets[i]) {
            app->plugIn(this);
            sockets[i] = app;
            return true;
        }
    }
    return false;
}

bool Socket::plugOut(Appliance* app)
{
    if (isDown() || !app) return false;

    for (unsigned i = 0; i < slots; ++i) {
        if (sockets[i] == app) {
            sockets[i] = nullptr;
            app->plugOut();
            return true;
        }
    }
    return false;
}

void Socket::notifyPowerChange()
{
    if (getCurrentPower() > maxPower) {
        unplugAll();
        down = true;
    }
}

double Socket::getCurrentPower() const
{
    double currConsumption = 0;
    for (unsigned i = 0; i < slots; ++i) {
        if (sockets[i]) {
            if (sockets[i]->isTurnedOn()) {
                currConsumption += sockets[i]->getPower();
            }
        }
    }
    return currConsumption;
}

void Socket::print() const
{
    std::cout << "Info for a multi-socket:\n"
        << "Slots: " << slots << "\n"
        << "Max power: " << maxPower << "\n";
    if (down) {
        std::cout << "It is already down! :(\n";
    }
    else {
        std::cout << "Sockets info:\n";
        for (unsigned i = 0; i < slots; ++i) {
            if (sockets[i]) {
                std::cout << "Socket " << i << " is connected with \n";
                sockets[i]->print(std::cout);
            } 
            else {
                std::cout << "Socket " << i << " is not connected\n";
            }
        }
    }
}

void Socket::unplugAll()
{
    for (unsigned i = 0; i < slots; ++i) {
        if (sockets[i])
            sockets[i]->turnOff();
    }
}
