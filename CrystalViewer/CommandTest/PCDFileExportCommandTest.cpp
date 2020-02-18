#include "pch.h"

#include "../Command/Command.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommand, TestExecute)
{
	World world;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto ps = world.getSceneFactory()->createParticleSystemScene(positions, ParticleAttribute(), "");
	world.getObjects()->addScene(ps);

	const std::vector<int> newIds = { ps->getId() };
	const std::string filePath = "./PCDFileExportTest.pcd";
	Command command(FileExportLabels::PCDFileExportCommandLabel);
	command.setArg(FileExportLabels::IdsLabel, newIds);
	command.setArg(FileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE( command.execute(&world) );
}