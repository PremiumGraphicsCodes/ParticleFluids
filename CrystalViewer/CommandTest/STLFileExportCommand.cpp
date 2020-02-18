#include "pch.h"

/*
#include "../Command/Command.h"

#include "../Command/Public/ParticleSystemCreateLabels.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(STLFileExportCommand, TestExecute)
{
	World world;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	Crystal::Command::Command command(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command.setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	EXPECT_TRUE(command.execute(&world));

	const auto newId = std::any_cast<int>(command.getResult(ParticleSystemCreateLabels::NewIdLabel));
	const std::vector<int> newIds = { newId };
	const std::string filePath = "./PCDFileExportTest.pcd";
	command.create(FileExportLabels::PCDFileExportCommandLabel);
	command.setArg(FileExportLabels::IdsLabel, newIds);
	command.setArg(FileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command.execute(&world));
}
*/