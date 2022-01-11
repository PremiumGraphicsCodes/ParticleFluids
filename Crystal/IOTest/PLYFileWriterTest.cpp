#include "gtest/gtest.h"

#include "../IO/PLYFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PLYFileWriterTest, TestWriteASCII)
{
	PLYFile ply;

	ply.vertices.push_back(PLYPoint(Vector3df(1, 2, 3)));
	ply.vertices.push_back(PLYPoint(Vector3dd(2, 3, 4)));
	ply.vertices.push_back(PLYPoint(Vector3dd(3, 4, 5)));

	PLYFileWriter writer;
	EXPECT_TRUE(writer.write("PLYWriteTestASCII.ply", ply));
}
