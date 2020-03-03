#include "gtest/gtest.h"

#include "../IO/PCDFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PCDFileWriterTest, TestWriter)
{
	PCDFile pcd;
	pcd.header.width = 3;
	pcd.data.positions.push_back(Vector3dd(1, 2, 3));
	pcd.data.positions.push_back(Vector3dd(2, 3, 4));
	pcd.data.positions.push_back(Vector3dd(3, 4, 5));

	PCDFileWriter writer;
	EXPECT_TRUE( writer.write("../PCDFileWriterTest.pcd", pcd) );
}
