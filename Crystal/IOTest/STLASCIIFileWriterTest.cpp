#include "gtest/gtest.h"

#include "../IO/STLASCIIFileWriter.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::IO;

TEST(STLASCIILFileWriterTest, TestWrite)
{
	const Triangle3d t1
	(
		Vector3dd(0, 1, 2),
		Vector3dd(3, 4, 5),
		Vector3dd(6, 7, 8)
	);
	const Triangle3d t2
	(
		Vector3dd(10, 11, 12),
		Vector3dd(13, 14, 15),
		Vector3dd(16, 17, 18)
	);
	const Triangle3d t3
	(
		Vector3dd(0, 0, 0),
		Vector3dd(1, 0, 0),
		Vector3dd(0, 1, 0)
	);


	STLFile stl;
	stl.header = "";
	stl.faceCount = 3;
	stl.faces.push_back(TriangleFace(t1, Vector3dd(0,0,1)));
	stl.faces.push_back(TriangleFace(t2, Vector3dd(0,0,1)));
	stl.faces.push_back(TriangleFace(t3, Vector3dd(0,0,1)));

	STLASCIIFileWriter writer;
	writer.write("STLASCIIFileWriterTest.stl", stl);
}
