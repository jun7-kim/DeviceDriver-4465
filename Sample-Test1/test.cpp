#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashMemoryDeviceAPIMock : public FlashMemoryDeviceAPI
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, ReadNormal) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x0)).Times(5).WillRepeatedly(Return(13));

	DeviceDriver device_driver(&flash_device_mock);
	EXPECT_THAT(device_driver.read(0x0), Eq(13));
}

TEST(TestCaseName, ReadException) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x0)).
		WillOnce(Return(13)).
		WillOnce(Return(13)).
		WillOnce(Return(13)).
		WillOnce(Return(12));
	
	DeviceDriver device_driver(&flash_device_mock);
	EXPECT_THROW(device_driver.read(0x0), ReadFailException);
}