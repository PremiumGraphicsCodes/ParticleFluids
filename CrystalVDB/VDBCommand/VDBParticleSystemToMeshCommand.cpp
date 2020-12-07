#include "VDBParticleSystemToMeshCommand.h"

#include "PublicLabels/VDBParticleSystemToMeshLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemToMeshCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	meshId(::MeshIdLabel, -1)
{
	add(&particleSystemId);
	add(&meshId);
}

VDBParticleSystemToMeshCommand::Results::Results()
{
}

VDBParticleSystemToMeshCommand::VDBParticleSystemToMeshCommand() :
	ICommand(&args, &results)
{}

std::string VDBParticleSystemToMeshCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBParticleSystemToMeshCommand::execute(World* world)
{
	/*
	OpenVDBFileReader reader;
	const auto isOk = reader.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto& names = reader.getPointGridNames();

	std::vector<int> newIds;
	for (auto n : names) {
		const auto& positions = reader.readPositions(n);
		ParticleAttribute attr;
		auto ps = std::make_unique< ParticleSystem<ParticleAttribute> >(positions, attr);
		ParticleSystemScene* scene = new ParticleSystemScene(world->getNextSceneId(), "", std::move(ps));
		world->getScenes()->addScene(scene);
		const auto newId = scene->getId();
		newIds.push_back(newId);
	}
	results.newIds.setValue(newIds);
	//reader.get
	return true;
	*/
	return false;
}
