#include "gtest/gtest.h"

#include "../IO/STLASCIIFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::IO;

TEST(STLASCIILFileWriterTest, TestWrite)
{
	STLFile stl;
	stl.header = "";
	stl.faceCount = 3;
//	stl.faces.push_back(TriangleFace()

//	STLASCIIFileWriter writer;
//	writer.write("STLASCIIFileWriterTest.stl", )
}
