#include <iostream>
#include <fstream>

#include "Server.h"
#include "DeviceFactory.h"

Server::Server(int capacity, unsigned timeout)
    : connections(new Connection*[capacity]{})
    , capacity(capacity)
    , timeout(timeout)
{
}

Server::~Server()
{
    for (unsigned i = 0; i < count; i++)
        delete connections[i];
    delete[] connections;
    connections = nullptr;
}

bool Server::Connect(const Device& device)
{
    return InsertConnection(new Connection{device.Clone(), currTime});
}

bool Server::Disconnect(unsigned deviceId)
{
    const int idx = FindDevice(deviceId);
    if (idx == -1)
        return false;

    RemoveConnection(idx);
    return true;
}

void Server::Tick(unsigned tickCount)
{
    currTime += tickCount;
    for (int i = 0; i < count; i++)
        if (currTime - connections[i]->time >= timeout)
            RemoveConnection(i--);
}

bool Server::SaveLog(const char* filename) const
{
    std::ofstream out(filename);
    if (!out)
        return false;

    for (int i = 0; i < count; i++)
    {
        connections[i]->SaveToLog(out);
        if (!out)
            return false;
    }

    out.close();

    if (!out)
        return false;
    return true;
}

bool Server::LoadLog(const char* filename)
{
    std::ifstream in(filename);
    if (!in)
        return false;

    Clear();  // breaks strong exception safety guarantee

    while (Connection* connection = Connection::FromLogFile(in))
        InsertConnection(connection);  // still weak exception safety guarantee

    return true;
}

void Server::Print() const
{
    std::cout << "Server has " << count << " connections:\n";
    for (int i = 0; i < count; i++)
    {
        std::cout << " - ";
        connections[i]->device->Print();
        std::cout << "\n";
    }
}

void Server::Clear()
{
    for (int i = 0; i < count; i++)
        RemoveConnection(0);
}

Server::Connection* Server::Connection::FromLogFile(std::ifstream& logFile)
{
    Device* device = DeviceFactory::CreateFromLog(logFile);
    unsigned time;
    logFile >> time;
    if (logFile)
        return new Connection{device, time};

    return nullptr;
}

Server::Connection::Connection(const Connection& other)
    : Connection(other.device->Clone(), other.time)
{
}

Server::Connection::~Connection()
{
    delete device;
    device = nullptr;
}

void Server::Connection::SaveToLog(std::ofstream& out) const
{
    device->SaveToLog(out);
    out << " " << time << "\n";
}

int Server::FindDevice(unsigned deviceId) const
{
    for (int i = 0; i < count; i++)
        if (connections[i]->device->GetId() == deviceId)
            return i;

    return -1;
}

bool Server::InsertConnection(Connection* connection)
{
    if (count >= capacity)
        return false;

    connections[count] = connection;
    count++;
    return true;
}

void Server::RemoveConnection(int idx)
{
    delete connections[idx];
    connections[idx] = connections[count - 1];
    connections[count - 1] = nullptr;
    count--;
}
