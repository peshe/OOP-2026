#include <iostream>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <fstream>

#pragma warning (disable : 4996)

class Device
{
public:
	Device()
		:Device("")
	{}

	Device(const char* name)
		:id(nextId++)
	{
		setName(name);
	}

	Device(const Device& other)
		:Device(other.name)
	{ }

	Device& operator=(const Device& other)
	{
		if (this != &other)
		{
			setName(other.name);
		}
		return *this;
	}

	virtual ~Device()
	{
		delete[] name;
	}

	void setName(const char* newName)
	{
		if (!newName) throw std::runtime_error("nullptr");
		char* temp = strcpy(new char[strlen(newName) + 1], newName);
		delete[] name;
		name = temp;
	}

	unsigned getId() const { return id; }
	const char* getName() const { return name; }

	virtual Device* clone() const = 0;
	virtual const char* getType() const = 0;
	virtual void print() const = 0;
	virtual void save(std::ofstream& ofs) const = 0;
	virtual void load(std::ifstream& ifs) = 0;

protected:
	const unsigned id;
	char* name = nullptr;

	static unsigned nextId;

	void swap(Device& other)
	{
		std::swap(name, other.name);
	}
};

void Device::print() const
{
	std::cout << name << '\n' << id << '\n';
}

void Device::save(std::ofstream& ofs) const
{
	ofs << id << ' ' << name << ' ';
}

void Device::load(std::ifstream& ifs)
{
	unsigned idbuf;
	char buffer[128];
	ifs >> idbuf >> buffer;
	setName(buffer);
}


class MobileDevice : public Device
{
public:
	MobileDevice()
		:MobileDevice("", 0)
	{ }

	MobileDevice(const char* name, unsigned batterylv)
		:Device(name)
	{
		setBatteryLv(batterylv);
	}

	void setBatteryLv(unsigned newBatteryLv)
	{
		if (newBatteryLv > 100) throw std::runtime_error("invalid arg");
		batteryLv = newBatteryLv;
	}

	unsigned getBatteryLv() const { return batteryLv; }

	Device* clone() const override
	{
		return new MobileDevice(*this);
	}
	const char* getType() const override
	{
		return "mobile";
	}

	void print() const override
	{
		Device::print();
		std::cout << batteryLv << '\n';
	}
	void save(std::ofstream& ofs) const override
	{
		Device::save(ofs);
		ofs << batteryLv << ' ';
	}

	void load(std::ifstream& ifs) override
	{
		Device::load(ifs);
		unsigned buffer;
		ifs >> buffer;
		setBatteryLv(buffer);
	}

private:
	unsigned batteryLv;
};


class DesktopDevice : public Device
{
public:
	DesktopDevice()
		:DesktopDevice("","")
	{ }

	DesktopDevice(const char* name, const char* ipAddr)
		:Device(name)
	{
		setIpAddress(ipAddr);
	}

	DesktopDevice(const DesktopDevice& other)
		:DesktopDevice(other.name, other.ipAddr)
	{}

	DesktopDevice& operator=(const DesktopDevice& other)
	{
		if (this != &other)
		{
			//cant do copy and swap because of id??
			char* temp = strcpy(new char[strlen(other.ipAddr) + 1], other.ipAddr);
			try
			{
				Device::operator=(other);
			}
			catch (...)
			{
				delete[] temp;
				throw;
			}
			delete[] ipAddr;
			ipAddr = temp;
		}
		return *this;
	}

	~DesktopDevice()
	{
		delete[] ipAddr;
	}

	void setIpAddress(const char* newIpAddr)
	{
		if (!newIpAddr) throw std::runtime_error("nullptr");
		char* temp = strcpy(new char[strlen(newIpAddr) + 1], newIpAddr);
		delete[] ipAddr;
		ipAddr = temp;
	}

	const char* getIpAddress() const { return ipAddr; }

	Device* clone() const override
	{
		return new DesktopDevice(*this);
	}
	const char* getType() const override
	{
		return "desktop";
	}

	void print() const override
	{
		Device::print();
		std::cout << ipAddr << '\n';
	}
	void save(std::ofstream& ofs) const override
	{
		Device::save(ofs);
		ofs << ipAddr << ' ';
	}

	void load(std::ifstream& ifs) override
	{
		Device::load(ifs);
		char buffer[128];
		ifs >> buffer;
		setIpAddress(buffer);
	}

private:
	char* ipAddr = nullptr;

	void swap(DesktopDevice& other)
	{
		Device::swap(other);
		std::swap(ipAddr, other.ipAddr);
	}
};

class Server;

class Connection
{
public:
	Connection& operator=(const Connection& other)
	{
		if (this != &other)
		{
			Device* temp = other.device->clone();
			delete device;
			device = temp;
			this->tick = tick;
		}
		return *this;
	}

	~Connection()
	{
		delete device;
	}

	unsigned getDeviceId() const { return device->getId(); }
	unsigned getConnectedAt() const { return tick; }
	Device& getDevice() { return *device; }
	const Device& getDevice() const { return *device; }	//should i have both?

	void save(std::ofstream& ofs) const
	{
		ofs << device->getType() << ' ';
		device->save(ofs);
		ofs << ' ' << tick << '\n';
	}

	static Connection* load(std::ifstream& ifs)
	{
		//this code should prob be separated in some other function but thats the idea
		char buffer[128];
		unsigned tick;
		ifs >> buffer;
		if (strcmp(buffer, "mobile") == 0)
		{
			MobileDevice mb;
			mb.load(ifs);
			ifs >> tick;
			return new Connection(mb, tick);
		}
		else if (strcmp(buffer, "desktop") == 0)
		{
			DesktopDevice dd;
			dd.load(ifs);
			ifs >> tick;
			return new Connection(dd, tick);
		}
		else throw std::runtime_error("invalid type");
	}


	//is this the idea?
	friend class Server;
private:
	Connection(const Device& d, unsigned tick)
	{
		device = d.clone();
		this->tick = tick;
	}

	Connection(const Connection& other)
		:Connection(*other.device, other.tick)
	{}


private:
	Device* device;
	unsigned tick;	//why is it int in the task descr?
};

class Server
{
public:
	Server(unsigned capacity, unsigned timeout)
		:cap(capacity), size(0), timeout(timeout), currTick(0)
	{
		connections = new Connection * [capacity] {};
	}

	~Server()
	{
		for (int i = 0; i < size; i++)
		{
			delete connections[i];
		}
		delete[] connections;
	}

	Server(const Server& other) = delete;
	Server& operator=(const Server& other) = delete;

	bool connect(const Device& d)
	{
		if (cap = size) return false;
		connections[size] = new (std::nothrow) Connection(d, currTick);
		if (!connections[size]) return false;
		size++;
	}

	bool disconnect(unsigned deviceId)
	{
		for (int i = 0; i < size; i++)
		{
			if (connections[i]->getDeviceId() == deviceId)
			{
				disconnectPr(i);
				return true;
			}
		}
		return false;
	}

	void tick(unsigned cnt = 1)
	{
		currTick += cnt;
		for (int i = 0; i < size; i++)
		{
			if (connections[i]->getConnectedAt() + timeout > currTick)
			{
				disconnectPr(i);
				i--;
			}
		}
	}

	void saveLog(const char* filename)
	{
		std::ofstream ofs(filename);
		if (!ofs.is_open()) throw std::runtime_error("cant open file");
		ofs << cap << ' ' << size << ' ' << timeout << ' ' << currTick << '\n';
		for (int i = 0; i < size; i++)
		{
			connections[i]->save(ofs);
		}
		if (!ofs) throw std::runtime_error("could not save");
	}

	void loadLog(const char* filename)
	{
		std::ifstream ifs(filename);
		if (!ifs.is_open()) throw std::runtime_error("cant open file");
		Connection** newConnections;
		unsigned newCap;
		unsigned newSize;
		unsigned newTimeout;
		unsigned newCurrTick;

		ifs >> newCap >> newSize >> newTimeout >> newCurrTick;
		newConnections = new Connection * [newCap] {};
		for (int i = 0; i < newSize; i++)
		{
			try
			{
				newConnections[i] = Connection::load(ifs);
			}
			catch (...)
			{
				for (int j = 0; j < i; j++)
				{
					delete newConnections[j];
				}
				delete[] newConnections;
				throw;
			}
		}

		if (ifs.fail() && !ifs.eof())
		{
			for (int j = 0; j < newSize; j++)
			{
				delete newConnections[j];
			}
			delete[] newConnections;
			throw std::runtime_error("could not read file");
		}
		

		for (int i = 0; i < size; i++)
		{
			delete connections[i];
		}
		delete[] connections;

		connections = newConnections;
		cap = newCap;
		size = newSize;
		timeout = newTimeout;
		currTick = newCurrTick;
	}

	unsigned getCapacity() const { return cap; }
	unsigned getCurrConnectionCnt() const { return size; }
	unsigned getTimeout() const { return timeout; }
	unsigned getCurrTick() const { return currTick; }

private:
	Connection** connections;
	unsigned cap;
	unsigned size;
	unsigned timeout;
	unsigned currTick;

	void disconnectPr(unsigned i)
	{
		delete connections[i];
		for (int j = i; j < size - 1; j++)
		{
			connections[j] = connections[j + 1];
		}
		connections[size - 1] = nullptr;
		size--;
	}

};

int main()
{
	//...
}