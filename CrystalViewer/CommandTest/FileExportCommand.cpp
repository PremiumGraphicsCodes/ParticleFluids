#include "pch.h"

#include "../Command/CommandFactory.h"
#include "../Command/Public/ParticleSystemCreateLabels.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(FileExportCommand, TestExportPCD)
{
	CommandFactory factory;
	World world;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto command = factory.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command->setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	EXPECT_TRUE(command->execute(&world));
//	const auto newId = std::any_cast<int>(command->getResult(ParticleSystemCreateLabels::NewIdLabel));

	const std::string filePath = "./TestExport.pcd";
	command = factory.create(::FileExportLabels::FileExportCommandLabel);
	//command->setArg(::FileExportLabels::IdsLabel, ids);
	command->setArg(::FileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command->execute(&world));
}