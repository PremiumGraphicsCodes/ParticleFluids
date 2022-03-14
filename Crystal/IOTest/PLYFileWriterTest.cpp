#include "gtest/gtest.h"

#include "../IO/PLYFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PLYFileWriterTest, TestWriteASCII)
{
	PLYFile ply;
	ply.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("z", PLYType::FLOAT));

	ply.addPoint(Vector3df(1, 2, 3));
	ply.addPoint(Vector3dd(2, 3, 4));
	ply.addPoint(Vector3dd(3, 4, 5));

	PLYFileWriter writer;
	EXPECT_TRUE(writer.writeASCII("PLYWriteTestASCII.ply", ply));
}

TEST(PLYFileWriterTest, TestWriteBinary)
{
	PLYFile ply;
	ply.properties.push_back(PLYProperty("x", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("y", PLYType::FLOAT));
	ply.properties.push_back(PLYProperty("z", PLYType::FLOAT));

	ply.addPoint(Vector3df(1, 2, 3));
	ply.addPoint(Vector3dd(2, 3, 4));
	ply.addPoint(Vector3dd(3, 4, 5));

	PLYFileWriter writer;
	EXPECT_TRUE(writer.writeBinary("PLYWriteTestBinary.ply", ply));
}
