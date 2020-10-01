#include "gtest/gtest.h"

#include "../OpenVDBConverter/OpenVDBFileReader.h"

using namespace Crystal::OpenVDB;

TEST(OpenVDBFileReaderTest, TestRead)
{
    OpenVDBFileReader reader;
    const auto isOk = reader.read("testWrite.vdb");
    EXPECT_TRUE(isOk);
    const auto positions = reader.getPositions();
    EXPECT_EQ(4, positions.size());
}
