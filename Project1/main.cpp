#include"gmock/gmock.h"
#include "DeviceDriver.h"
#include "FlashMemoryDevice.h"

using namespace testing;
using namespace std;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

class Application {
public :
	Application(DeviceDriver &dd) : dd_(&dd)  {

	}

private:
	DeviceDriver* dd_;
};


TEST(DeviceDriverTestRead, 200ms_단위로_Read를_5회_수행) {
	// 5회 함수가 호출 되어야 PASS야
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA)).Times(5);

	dd.read(0xA);
}

TEST(DeviceDriverTestRead, 5회의_Read의_결과가_모두_같은_값일_때,_읽은_값을_return) {
	// 5회의 Read의 결과가 모두 같은 값일 때, 읽은 값을 return 한다.
	// 모두 같은 값이 아니라면, Custom Exception(ReadFailException)을 발생

}


int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}