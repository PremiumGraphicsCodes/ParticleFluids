#include "PSToVolumeView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../VDBConverter/ParticleSystemToVolumeConverter.h"
#include "../VDBConverter/VolumeToMeshConverter.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

PSToVolumeView::PSToVolumeView(World* model, Canvas* canvas) :
	IOkCancelView("FluidSimulation", model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas)
{
	add(&particleSystemSelectView);
}

void PSToVolumeView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}

	VDBParticleSystem ps;
	ps.fromCrystal(*scene->getShape());

	ParticleSystemToVolumeConverter converter;
	auto volume = converter.toVolume(ps);

	VolumeToMeshConverter toMeshConverter;
	auto mesh = toMeshConverter.toMesh(*volume);

	mesh->toCrystal();
}

