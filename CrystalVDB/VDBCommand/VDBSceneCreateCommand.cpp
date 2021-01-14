#include "VDBSceneCreateCommand.h"

#include "../../CrystalVDB/CrystalVDB/VDBParticleSystemScene.h"
#include "../../CrystalVDB/CrystalVDB/VDBPolygonMeshScene.h"
#include "../../CrystalVDB/CrystalVDB/VDBVolumeScene.h"

#include "PublicLabels/VDBSceneCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::VDB;

VDBSceneCreateCommand::Args::Args() :
	sceneType(::SceneTypeLabel, ::SceneType_VDBPointsLabel),
	name(::NameLabel, "")
{
	add(&sceneType);
	add(&name);
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
	const auto name = args.name.getValue();
	if (typeName == ::SceneType_VDBPointsLabel) {
		auto mesh = new VDBParticleSystemScene(world->getNextSceneId(), name);
		world->addScene(1, mesh);
		results.newId.setValue(mesh->getId());
	}
	else if (typeName == ::SceneType_VDBMeshLabel) {
		auto mesh = new VDBPolygonMeshScene(world->getNextSceneId(), name);
		world->addScene(1, mesh);
		results.newId.setValue(mesh->getId());
	}
	else if (typeName == ::SceneType_VDBVolumeLabel) {
		auto mesh = new VDBVolumeScene(world->getNextSceneId(), name);
		world->addScene(1, mesh);
		results.newId.setValue(mesh->getId());
	}
	else {
		assert(false);
		return false;
	}
	return true;
}
