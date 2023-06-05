#include <exception>

#include "DeviceDriver.h"
#include "windows.h"

using namespace std;

class ReadFailException : public exception
{
public:
	const char* what()
	{
		return "ReadFailException is occurred";
	}
};

DeviceDriver::DeviceDriver(FlashMemoryDeviceAPI* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	int value = (int)(m_hardware->read(address));
	int new_value;
	for (int i = 0; i < (repeat_read_cnt - 1); i++)
	{
		waitDelay();
		new_value = (int)(m_hardware->read(address));
		if (value != new_value) {
			throw ReadFailException();
		}
	}

	return value;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::waitDelay()
{
	Sleep(200);
}
