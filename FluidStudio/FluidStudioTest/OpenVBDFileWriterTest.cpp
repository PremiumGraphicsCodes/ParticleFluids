#include "pch.h"
#include "../FluidStudio/OpenVDBFileWriter.h"

using namespace Crystal::OpenVDB;

TEST(OpenVDBFileWriterTest, TestWriter)
{
	openvdb::initialize();

	OpenVDBFileWriter writer;
	writer.addPoint(openvdb::Vec3R(0, 1, 0));
	writer.addPoint(openvdb::Vec3R(1.5, 3.5, 1));
	writer.addPoint(openvdb::Vec3R(-1, 6, -2));
	writer.addPoint(openvdb::Vec3R(1.1, 1.25, 0.06));

	writer.setName("Points");
	writer.write("testWrite.vdb");
}