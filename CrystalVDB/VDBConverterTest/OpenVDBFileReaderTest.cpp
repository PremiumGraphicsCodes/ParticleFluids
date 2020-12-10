#include "gtest/gtest.h"

#include "../VDBConverter/VDBFileReader.h"

using namespace Crystal::VDB;

TEST(OpenVDBFileReaderTest, TestRead)
{
    VDBFileReader reader;
    const auto isOk = reader.open("testWrite.vdb");
    EXPECT_TRUE(isOk);
    const auto& names = reader.getPointGridNames();
    const auto positions = reader.readPositions(names[0]);
    EXPECT_EQ(4, positions.size());
    reader.close();
}
