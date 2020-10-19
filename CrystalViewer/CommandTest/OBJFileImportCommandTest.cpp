#include "pch.h"

#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/Public/OBJFileImportLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(OBJFileImportCommandTest, TestExecute)
{
	World world;

	const std::string filePath = "OBJFileImportTest.obj";
	auto command = CommandFactory::create(OBJFileImportLabels::CommandNameLabel);
	command->setArg(OBJFileImportLabels::FilePathLabel, filePath);
	const auto isOk = command->execute(&world);
	EXPECT_TRUE(isOk);
	const auto newId = std::any_cast<int>( command->getResult(OBJFileImportLabels::NewIdLabel) );
	EXPECT_EQ(1, newId);
}