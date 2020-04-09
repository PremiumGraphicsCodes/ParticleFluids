#include "pch.h"

#include "../Command/Command.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../Command/Public/PCDFileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommand, TestExecute)
{
	World world;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto ps = new ParticleSystemScene(1, positions, ParticleAttribute(), "");
	world.getObjects()->addScene(ps);

	const std::vector<int> newIds = { ps->getId() };
	const std::string filePath = "PCDFileExportTest.pcd";
	Command command(PCDFileExportLabels::CommandNameLabel);
	command.setArg(PCDFileExportLabels::IdsLabel, newIds);
	command.setArg(PCDFileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE( command.execute(&world) );
}