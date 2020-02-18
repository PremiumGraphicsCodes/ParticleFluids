#include "pch.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/ParticleAttribute.h"

#include "../Command/Command.h"
#include "../Command/Public/FileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(FileExportCommand, TestExportPCD)
{
	World world;

	const std::vector<Vector3dd> positions = { Vector3dd(0,0,0) };
	auto ps = world.getSceneFactory()->createParticleSystemScene(positions, ParticleAttribute(), "");
	world.getObjects()->addScene(ps);

	const std::string filePath = "./TestExport.pcd";
	Crystal::Command::Command command(::FileExportLabels::FileExportCommandLabel);
	//command->setArg(::FileExportLabels::IdsLabel, ids);
	command.setArg(::FileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE(command.execute(&world));
}