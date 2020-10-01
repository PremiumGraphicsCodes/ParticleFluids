#include "gtest/gtest.h"
#include "../OpenVDBConverter/OpenVDBAdapter.h"

int main(int argc, char** argv) {
//	std::cout << "hello" << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	Crystal::OpenVDB::OpenVDBAdapter::init();
	return RUN_ALL_TESTS();
}