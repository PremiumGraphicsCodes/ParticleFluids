#include "gtest/gtest.h"
#include "openvdb/openvdb.h"

int main(int argc, char** argv) {
//	std::cout << "hello" << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	::openvdb::initialize();
	return RUN_ALL_TESTS();
}