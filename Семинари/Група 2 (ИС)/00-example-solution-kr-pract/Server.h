#pragma once

#include <iosfwd>
#include "Device.h"

class Server
{
public:
    Server(int capacity, unsigned timeout);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    ~Server();

    bool Connect(const Device& device);
    bool Disconnect(unsigned deviceId);
    void Tick(unsigned cnt = 1);

    bool SaveLog(const char* filename) const;
    bool LoadLog(const char* filename);

    void Print() const;
    void Clear();

private:
    struct Connection
    {
        Connection(Device* device, unsigned time) : device(device), time(time) {}
        static Connection* FromLogFile(std::ifstream& logFile);

        Connection(const Connection& other);
        Connection& operator=(const Connection& other) = delete;
        ~Connection();

        void SaveToLog(std::ofstream& out) const;

        Device* device = nullptr;
        unsigned time;
    };

    int FindDevice(unsigned deviceId) const;
    bool InsertConnection(Connection* connection);
    void RemoveConnection(int idx);

private:
    unsigned timeout = 0;
    unsigned currTime = 0;

    int capacity = 0;
    int count = 0;
    Connection** connections = nullptr;
};

