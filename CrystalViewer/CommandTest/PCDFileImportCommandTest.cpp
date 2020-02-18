#include "pch.h"

#include "../Command/Command.h"

#include "../Command/Public/FileImportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileImportCommand, TestExecute)
{
	World world;

	const std::string filePath = "./PCDFileImportTest.pcd";
	Command command(FileImportLabels::PCDFileImportCommandLabel);
	command.setArg(FileImportLabels::FilePathLabel, filePath);
	EXPECT_TRUE( command.execute(&world) );

	const auto id = std::any_cast<int>( command.getResult(FileImportLabels::NewIdLabel) );
	EXPECT_EQ(1, id);
}