#include <vector>

#include "DeviceDriver.h"

using namespace std;

class Application
{
public:
	Application(DeviceDriver* device_driver) : m_device_driver(device_driver)
	{}

	vector<int> ReadAndPrint(long startAddr, long endAddr)
	{
		vector<int> result;
		for (int i = startAddr; i <= endAddr; i++)
		{
			result.push_back(m_device_driver->read(i));
		}
		return result;
	}

	void WriteAll(int data)
	{
		for (int i = 0x0; i <= 0x4; i++)
		{
			m_device_driver->write(i, data);
		}
	}

private:
	DeviceDriver* m_device_driver;
};
