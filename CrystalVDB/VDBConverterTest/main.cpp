#include "gtest/gtest.h"
#include "../VDBConverter/VDBAdapter.h"

int main(int argc, char** argv) {
//	std::cout << "hello" << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	Crystal::VDB::VDBAdapter::init();
	return RUN_ALL_TESTS();
}