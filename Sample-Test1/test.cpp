#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/App.cpp"

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

TEST(TestCaseName, WriteNormal) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x0)).WillRepeatedly(Return(0xff));

	DeviceDriver device_driver(&flash_device_mock);
	EXPECT_NO_THROW(device_driver.write(0x0, 0xba));
}

TEST(TestCaseName, WriteException) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x0)).WillRepeatedly(Return(0x1));

	DeviceDriver device_driver(&flash_device_mock);
	EXPECT_THROW(device_driver.write(0x0, 0xba), WriteFailException);
}

TEST(TestCaseName, ReadAndPoint) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x2)).WillRepeatedly(Return(0x20));
	EXPECT_CALL(flash_device_mock, read(0x3)).WillRepeatedly(Return(0x30));
	EXPECT_CALL(flash_device_mock, read(0x4)).WillRepeatedly(Return(0x40));

	DeviceDriver device_driver(&flash_device_mock);
	Application app(&device_driver);

	vector<int> result;
	result = app.ReadAndPrint(0x2, 0x4);
	EXPECT_THAT(result[0], Eq(0x20));
	EXPECT_THAT(result[1], Eq(0x30));
	EXPECT_THAT(result[2], Eq(0x40));
}

TEST(TestCaseName, WriteAll) {
	FlashMemoryDeviceAPIMock flash_device_mock;
	EXPECT_CALL(flash_device_mock, read(0x0)).WillOnce(Return(0xff));
	EXPECT_CALL(flash_device_mock, read(0x1)).WillOnce(Return(0xff));
	EXPECT_CALL(flash_device_mock, read(0x2)).WillOnce(Return(0xff));
	EXPECT_CALL(flash_device_mock, read(0x3)).WillOnce(Return(0xff));
	EXPECT_CALL(flash_device_mock, read(0x4)).WillOnce(Return(0xff));

	EXPECT_CALL(flash_device_mock, write(0x0, 0xba)).Times(1);
	EXPECT_CALL(flash_device_mock, write(0x1, 0xba)).Times(1);
	EXPECT_CALL(flash_device_mock, write(0x2, 0xba)).Times(1);
	EXPECT_CALL(flash_device_mock, write(0x3, 0xba)).Times(1);
	EXPECT_CALL(flash_device_mock, write(0x4, 0xba)).Times(1);

	DeviceDriver device_driver(&flash_device_mock);
	Application app(&device_driver);

	EXPECT_NO_THROW(app.WriteAll(0xba));
}
