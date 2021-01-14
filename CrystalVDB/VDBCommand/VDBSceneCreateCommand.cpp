#include "VDBSceneCreateCommand.h"

#include "../../CrystalVDB/CrystalVDB/VDBParticleSystemScene.h"

#include "PublicLabels/VDBSceneCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::VDB;

VDBSceneCreateCommand::Args::Args() :
	sceneType(::SceneTypeLabel, ::SceneType_VDBPointsLabel)
{
}

VDBSceneCreateCommand::Results::Results() :
	newId(::NewIdLabel, -1)
{
	add(&newId);
}

std::string VDBSceneCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneCreateCommand::execute(World* world)
{
	const auto typeName = args.sceneType.getValue();
	if (typeName == ::SceneType_VDBPointsLabel) {
		auto mesh = new VDBParticleSystemScene(world->getNextSceneId(), "VDBPS");
		world->addScene(1, mesh);
		results.newId.setValue(mesh->getId());
	}
	else {
		assert(false);
		return false;
	}
	return true;
}
