#include "pch.h"

#include "../Command/Command.h"
#include "../Command/CommandFactory.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../Command/Public/PCDFileExportLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TEST(PCDFileExportCommand, TestExecute)
{
	World world;

	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>();
	shape->add(Vector3dd(0, 0, 0), ParticleAttribute());
	auto ps = new ParticleSystemScene(1, "", std::move(shape));
	world.getScenes()->addScene(ps);

	const std::vector<int> newIds = { ps->getId() };
	const std::string filePath = "PCDFileExportTest.pcd";
	auto command = CommandFactory::create(PCDFileExportLabels::CommandNameLabel);
	command->setArg(PCDFileExportLabels::IdsLabel, newIds);
	command->setArg(PCDFileExportLabels::FilePathLabel, filePath);
	EXPECT_TRUE( command->execute(&world) );
}