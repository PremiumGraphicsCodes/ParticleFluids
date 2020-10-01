#include "gtest/gtest.h"

#include "../OpenVDBConverter/OpenVDBFileReader.h"

using namespace Crystal::OpenVDB;

TEST(OpenVDBFileReaderTest, TestRead)
{
    OpenVDBFileReader reader;
    reader.read("testWrite.vdb");
    const auto positions = reader.getPositions();
    EXPECT_EQ(4, positions.size());
}
