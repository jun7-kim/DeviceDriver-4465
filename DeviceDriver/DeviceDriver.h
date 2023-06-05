#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
	DeviceDriver(FlashMemoryDeviceAPI* hardware);
	int read(long address);
	void write(long address, int data);

private:
	void waitDelay();

protected:
	FlashMemoryDeviceAPI* m_hardware;

private:
	const int repeat_read_cnt = 5;
};