#include "pch.h"

#include "../Command/Command.h"
#include "../Command/CommandFactory.h"

#include "../Command/Public/PCDFileImportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileImportCommand, TestExecute)
{
	World world;

	const std::string filePath = "./PCDFileImportTest.pcd";
	auto command = CommandFactory::create(PCDFileImportLabels::CommandNameLabel);
	command->setArg(PCDFileImportLabels::FilePathLabel, filePath);
	const auto isOk = command->execute(&world);
	EXPECT_TRUE(isOk);

	const auto id = std::any_cast<int>( command->getResult(PCDFileImportLabels::NewIdLabel) );
	EXPECT_EQ(1, id);
}