#include "gtest/gtest.h"

#include "../IO/PCDBinaryFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PCDBinaryFileWriterTest, TestWriter)
{
	PCDFile pcd;
	pcd.header.width = 3;
	pcd.header.points = 3;
	pcd.data.positions.push_back(Vector3dd(1, 2, 3));
	pcd.data.positions.push_back(Vector3dd(2, 3, 4));
	pcd.data.positions.push_back(Vector3dd(3, 4, 5));

	PCDBinaryFileWriter writer;
	EXPECT_TRUE(writer.write("PCDBinaryFileWriterTest.pcd", pcd));
}
