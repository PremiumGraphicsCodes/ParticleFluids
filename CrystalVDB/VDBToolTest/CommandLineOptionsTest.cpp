#include "pch.h"
#include "../VDBTool/CommandLineOptions.h"

using namespace Crystal::VDBTool;

TEST(CommandLineOptionsTest, Test)
{
	CommandLineOptions opt;
	std::vector<std::string> strs;
	strs.emplace_back("-i");
	strs.emplace_back("input.pcd");
	strs.emplace_back("-o");
	strs.emplace_back("output.stl");
	strs.emplace_back("-r");
	strs.emplace_back("0.1");
	strs.emplace_back("-v");
	strs.emplace_back("0.05");
	opt.parse(strs);

	EXPECT_EQ(opt.inputPsFilePath, "input.pcd");
	EXPECT_EQ(opt.outputMeshFilePath, "output.stl");
	EXPECT_DOUBLE_EQ(opt.particleRadius, 0.1);
	EXPECT_DOUBLE_EQ(opt.voxelSize, 0.05);
}