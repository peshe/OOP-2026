#pragma once

class Appliance;

class Socket
{
public:
    Socket(unsigned slots, double power);
    Socket(const Socket& s);
    ~Socket() noexcept;
    Socket& operator=(const Socket& s);

    bool plugIn(Appliance* app);
    bool plugOut(Appliance* app);
    void notifyPowerChange();

    void print() const;
    bool isDown() const { return down; }
    double getMaxPower() const { return maxPower; }
    double getCurrentPower() const;

private:
    void unplugAll();
    const unsigned slots;
    double maxPower;
    bool down = false;

    Appliance** sockets;
};
