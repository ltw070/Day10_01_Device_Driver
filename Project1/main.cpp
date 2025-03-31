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
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA)).Times(5);

	dd.read(0xA);
}

TEST(DeviceDriverTestRead, 5회의_Read의_결과가_모두_같은_값일_때,_읽은_값을_return) {
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB));

	EXPECT_EQ(dd.read(0xA), 0xB);
}

TEST(DeviceDriverTestRead, 5회의_Read의_결과가_모두_같은_값일_때_읽은_값을_return) {
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xB))
		.WillOnce(Return(0xC));

	EXPECT_THROW(dd.read(0xA), std::exception);
}


TEST(DeviceDriverTestWrite, 해당_객체에_이미_값이_적혀_있는지_확인) {
	//(읽었을 때 0xFF라면, 값이 지워진 상태이다.)
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA))
		.WillOnce(Return(0xFF));

	EXPECT_THROW(dd.write(0xA, 3), std::exception);
}

//값이 적혀 있지 않을 때, 해당 주소에 값을 Write한다.
//• 이미 값이 적혀 있다면 Custom Exception(WriteFailException)을 발생시킨다.

int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}