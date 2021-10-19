#include "gtest/gtest.h"

#include "../IO/TXTFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(TXTFileWriterTest, TestWrite)
{
	std::vector<Vector3dd> positions;
	positions.emplace_back(0, 1, 2);
	positions.emplace_back(3, 4, 5);
	positions.emplace_back(6, 7, 8);

	TXTFileWriter writer;
	const auto isOk = writer.write("TXTFileWriterTest.txt", positions);
	EXPECT_TRUE(isOk);
}