#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <stdexcept>

#include "Appliance.h"
#include "Socket.h"

unsigned Appliance::nextSN = 0;

Appliance::Appliance()
    :Appliance("Empty", "Noname", 0)
{}

Appliance::Appliance(const char* desc, const char* br, float power)
    : description(nullptr)
    , brand(nullptr)
    , power(power)
    , sn(Appliance::getSN())
{
    if (power < 0 || !isStringOK(desc) || !isStringOK(br)) {
        throw std::invalid_argument("Bad arguments passed to ctor.");
    }
    try {
        description = strcpy(new char[strlen(desc) + 1], desc);
        brand = strcpy(new char[strlen(br) + 1], br);
    }
    catch (const std::bad_alloc&) {
        delete[] description;
        throw;
    }
}

Appliance::Appliance(const Appliance& app)
    :Appliance(app.description, app.brand, app.power)
{}

Appliance::Appliance(Appliance&& app) noexcept
    : description(nullptr)
    , brand(nullptr)
    , power(app.power)
    , sn(Appliance::getSN())
{
    std::swap(description, app.description);
    std::swap(brand, app.brand);
}

Appliance::~Appliance()noexcept
{
    plugOut();
    delete[] brand;
    delete[] description;
}

Appliance& Appliance::operator=(const Appliance& other)
{
    if (this != &other) {
        char* desc = nullptr, *br = nullptr;
        try {
            desc = strcpy(new char[strlen(other.description) + 1], other.description);
            br = strcpy(new char[strlen(other.brand) + 1], other.brand);
        }
        catch (...) {
            delete[] desc;
            throw;
        }

        plugOut();
        power = other.power;
        delete[] description;
        description = desc;
        delete[] brand;
        brand = br;
    }
    return *this;
}

Appliance& Appliance::operator=(Appliance&& other) noexcept
{
    if (this != &other) {
        plugOut();
        power = other.power;
        std::swap(description, other.description);
        std::swap(brand, other.brand);
    }
    return *this;
}

void Appliance::print(std::ostream& os) const
{
    os << description << "\n";
    os << brand << "\n";
    os << power << " wats. ";
    os << "Serial number: " << sn;
    os << " is " << (isPluggedIn()?"plugged":"not plugged and");
    os << " and is turned " << (isTurnedOn() ? "on" : "off") << "\n";
}

bool Appliance::read(std::istream& is)
{
    if (!is) return false;

    char* desc = readLine(is);
    char* br = readLine(is);
    float power = 0;
    is >> power;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!is || !isStringOK(desc) || !isStringOK(br) || power <= 0) {
        delete[] desc;
        delete[] br;
        return false;
    }

    plugOut();
    setPower(power);
    delete[] description;
    description = desc;
    delete[] brand;
    brand = br;

    return true;
}

bool Appliance::setDescription(const char* desc)
{
    return Appliance::setString(description, desc);
}

bool Appliance::setBrand(const char* br)
{
    return Appliance::setString(brand, br);
}

bool Appliance::setPower(float p)
{
    if (isPluggedIn()) return false;
    if (p <= 0) return false;
    power = p;
    return true;
}

bool Appliance::turnOn()
{
    if (isPluggedIn() && !isTurnedOn()) {
        turnedOn = true;
        socket->notifyPowerChange();
        return true;
    }
    else {
        return false;
    }
}

bool Appliance::turnOff()
{
    if (isTurnedOn()){
        turnedOn = false;
        socket->notifyPowerChange();
        return true;
    }
    else {
        return false;
    }
}

bool Appliance::plugIn(Socket* s)
{
    if (s && s != socket && !isPluggedIn()) {
        socket = s;
        pluggedIn = s->plugIn(this);
        if (!pluggedIn) socket = nullptr;
        return pluggedIn;
    }
    else {
        return false;
    }
}

bool Appliance::plugOut()
{
    if (isPluggedIn()) {
        turnOff();
        socket->plugOut(this);
        socket = nullptr;
        pluggedIn = false;
        return true;
    } 
    else {
        return false;
    }
}

unsigned Appliance::getSN()
{
    return nextSN++;
}

char* Appliance::readLine(std::istream& is)
{
    if (!is) return nullptr;

    int len = 1024;
    char* buff = new(std::nothrow)char[len];
    int size = 0;
    if (!buff) return buff;
    char ch = 0;
    while (is.get(ch) && ch != '\n') {
        if (size == len - 1) {
            buff[size] = '\0';
            len *= 2;
            char* newBuf = new(std::nothrow)char[len];
            if (!newBuf) {
                delete[] buff;
                return nullptr;
            }
            strcpy(newBuf, buff);
            delete[] buff;
            buff = newBuf;
        }
        buff[size++] = ch;
    }
    buff[size] = '\0';
    return buff;
}

bool Appliance::setString(char*& dest, const char* src)
{
    if (!isStringOK(src)) return false;
    char* str = new (std::nothrow) char[strlen(src) + 1];
    if (!str) return false;
    delete[] dest;
    dest = strcpy(str, src);
    return true;
}
