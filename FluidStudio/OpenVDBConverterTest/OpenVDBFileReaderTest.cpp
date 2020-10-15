#include "gtest/gtest.h"

#include "../OpenVDBConverter/OpenVDBFileReader.h"

using namespace Crystal::OpenVDB;

TEST(OpenVDBFileReaderTest, TestRead)
{
    OpenVDBFileReader reader;
    const auto isOk = reader.open("testWrite.vdb");
    EXPECT_TRUE(isOk);
    const auto& names = reader.getPointGridNames();
    const auto positions = reader.readPositions(names[0]);
    EXPECT_EQ(4, positions.size());
    reader.close();
}
