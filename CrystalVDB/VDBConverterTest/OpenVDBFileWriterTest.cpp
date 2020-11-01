#include "gtest/gtest.h"

#include "../VDBConverter/OpenVDBFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

TEST(OpenVDBFileWriterTest, TestWrite)
{
    OpenVDBFileWriter writer;

    std::vector<Vector3dd> positions;
    positions.push_back(Vector3dd(0, 1, 0));
    positions.push_back(Vector3dd(1.5, 3.5, 1));
    positions.push_back(Vector3dd(-1, 6, -2));
    positions.push_back(Vector3dd(1.1, 1.25, 0.06));

    writer.open("testWrite.vdb");
    writer.write("points", positions);
    writer.close();
}
