#include "gtest\gtest.h"
#include "../IO/PCDBinaryFileReader.h"

using namespace Crystal::IO;

// from http://pointclouds.org/documentation/tutorials/pcd_file_format.php
TEST(PCDBinaryFileReaderTest, TestRead)
{
	PCDBinaryFileReader reader;
	EXPECT_TRUE(reader.read("./PCDBinaryFileWriterTest.pcd"));

	const auto& pcd = reader.getPCD();
	EXPECT_EQ(3, pcd.data.positions.size()) << std::endl;
}
