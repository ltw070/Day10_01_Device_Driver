#include "DeviceDriver.h"
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

// ����� ���� ���� Ŭ����
class ReadFailException : public std::exception {
public:
	// ���� �޽��� ��ȯ
	const char* what() const noexcept override {
		return "Read ����ġ!";
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

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}