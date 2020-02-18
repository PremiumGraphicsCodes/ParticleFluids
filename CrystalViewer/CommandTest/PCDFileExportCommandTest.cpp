#include "pch.h"

#include "../Command/CommandFactory.h"

#include "../Command/Public/ParticleSystemCreateLabels.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommand, TestExecute)
{
	World world;
	CommandFactory factory;
	
	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto command = factory.create(ParticleSystemCreateLabels::ParticleSystemAddLabel);
	command->setArg(ParticleSystemCreateLabels::PositionsLabel, positions);
	command->execute(&world);

	const auto newId = std::any_cast<int>( command->getResult(ParticleSystemCreateLabels::NewIdLabel) );
	
	const std::vector<int> newIds = { newId };
	const std::string filePath = "./PCDFileExportTest.pcd";
	command = factory.create(FileExportLabels::PCDFileExportCommandLabel);
	command->setArg(FileExportLabels::IdsLabel, newIds);
	command->setArg(FileExportLabels::FilePathLabel, filePath);
	command->execute(&world);
}