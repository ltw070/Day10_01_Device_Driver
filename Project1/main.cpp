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


TEST(DeviceDriverTestRead, 200ms_������_Read��_5ȸ_����) {
	MockFlashMemoryDevice mfd;
	DeviceDriver dd(&mfd);

	EXPECT_CALL(mfd, read(0xA)).Times(5);

	dd.read(0xA);
}

TEST(DeviceDriverTestRead, 5ȸ��_Read��_�����_���_����_����_��,_����_����_return) {
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

TEST(DeviceDriverTestRead, 5ȸ��_Read��_�����_���_����_����_��_����_����_return) {
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



int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}