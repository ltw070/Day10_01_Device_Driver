#include "DeviceDriver.h"
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

class ReadFailException : public std::exception {
public:
	const char* what() const noexcept override {
		return "Read 불일치!";
	}
};

int DeviceDriver::read(long address)
{
	// TODO: implement this method properly

	int ret = m_hardware->read(address);
	//try {
		for (int n = 0; n < 4; n++) {
			if (ret == m_hardware->read(address)) continue;
			throw ReadFailException();
		}
	//}
	//catch (std::exception& e) {
	//	return -1;
	//}

	return ret;
}

class WriteFailException : public std::exception {
public:
	const char* what() const noexcept override {
		return "이미 값이 적혀 있음!";
	}
};

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	if (m_hardware->read(address) == 0xFF) {
		throw WriteFailException();
		return;
	}

	m_hardware->write(address, (unsigned char)data);
}