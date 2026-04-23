#pragma once

#include <iostream>

class Socket;

class Appliance
{
public:
    Appliance();
    Appliance(const char* desc, const char* br, float power);
    Appliance(const Appliance& app);
    Appliance(Appliance&& app) noexcept;
    ~Appliance() noexcept;
    Appliance& operator=(const Appliance& app);
    Appliance& operator=(Appliance&& app) noexcept;

    void print(std::ostream& os) const;
    bool read(std::istream& is);

    const char* getDescription() const { return description; }
    const char* getBrand() const { return brand; }
    float getPower() const { return power; }
    bool isPluggedIn() const { return pluggedIn; }
    bool isTurnedOn() const { return turnedOn; }

    bool setDescription(const char* desc);
    bool setBrand(const char* brand);
    bool setPower(float power);
    
    bool turnOn();
    bool turnOff();
    bool plugIn(Socket* s);
    bool plugOut();

private:
    static unsigned getSN();
    static char* readLine(std::istream& is);
    static bool isStringOK(const char* str) { return str && *str; }
    static bool setString(char*& dest, const char* src);

private:
    char* description;
    char* brand;
    float power;
    bool pluggedIn = false;
    bool turnedOn = false;
    Socket* socket = nullptr;
    const unsigned sn;

    static unsigned nextSN;
};

