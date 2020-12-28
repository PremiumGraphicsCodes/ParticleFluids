#include "PSToVolumeView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../VDBConverter/ParticleSystemToVolumeConverter.h"
#include "../VDBConverter/VolumeToMeshConverter.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

PSToVolumeView::PSToVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas),
	radiusView("Radius", 5.0),
	materialView("Material", model)
{
	add(&particleSystemSelectView);
	add(&radiusView);
	add(&materialView);
}

void PSToVolumeView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}

	VDBParticleSystem ps;
	auto particles = scene->getShape()->getParticles();
	for (auto p : scene->getShape()->getParticles()) {
		ps.add(p->getPosition(), p->getAttribute().size);
	}

	ParticleSystemToVolumeConverter converter;
	auto volume = converter.toVolume(ps, radiusView.getValue());
	std::cout << "voxels = " << volume->getActiveVoxelCount() << std::endl;;
}