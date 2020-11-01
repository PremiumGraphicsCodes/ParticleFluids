#include "pch.h"

#include "../FluidStudio/FSProjFileWriter.h"

using namespace PG::FS;

//TEST(FSProjFileWriterTest, TestWrite)
//{
//	FSScene scene;
//	scene.args.maxTimeStep = 0.03;
//
//	FSProjFileWriter writer;
//	const auto actual = writer.write(scene);
//	const double value = actual["MaxTimeStep"];
//	EXPECT_EQ(value, 0.03);
//	//reader.read();
//}