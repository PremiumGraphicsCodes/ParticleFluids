#include "VDBParticleSystemToMeshCommand.h"

#include "PublicLabels/VDBParticleSystemToMeshLabels.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../VDBConverter/VDBParticleSystem.h"
#include "../VDBConverter/ParticleSystemToVolumeConverter.h"
#include "../VDBConverter/VolumeToMeshConverter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemToMeshCommand::Args::Args() :
	particleSystemId(::ParticleSystemIdLabel, -1),
	meshId(::MeshIdLabel, -1),
	materialId(::MaterialIdLabel, -1),
	radius(::RadiusLabel, 5.0)
{
	add(&particleSystemId);
	add(&meshId);
	add(&materialId);
	add(&radius);
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
	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(args.particleSystemId.getValue());
	if (scene == nullptr) {
		return false;
	}
	auto meshScene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	if (meshScene == nullptr) {
		return false;
	}
	auto materialScene = world->getScenes()->findSceneById<MaterialScene*>(args.materialId.getValue());
	if (materialScene == nullptr) {
		return false;
	}

	VDBParticleSystem ps;
	auto particles = scene->getShape()->getParticles();
	for (auto p : scene->getShape()->getParticles()) {
		ps.add(p->getPosition(), p->getAttribute().size);
	}
	ParticleSystemToVolumeConverter toVolumeConverter;
	auto volume = toVolumeConverter.toVolume(ps, args.radius.getValue());

	VolumeToMeshConverter toMeshConvereter;
	auto mesh = toMeshConvereter.toMesh(*volume);

	auto cMesh = mesh->toCrystal();
	meshScene->clear();
	meshScene->setShape(std::move(cMesh));
	Crystal::Scene::PolygonMeshScene::FaceGroup group(meshScene->getShape()->getFaces(), materialScene);
	meshScene->addGroup(group);
	
	return false;
}
