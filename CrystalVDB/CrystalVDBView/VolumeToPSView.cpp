#include "VolumeToPSView.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBVolumeConverter.h"

#include <iostream>

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VolumeToPSView::VolumeToPSView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	vdbVolumeSelectView("VDBVolume", model, canvas)
{
	add(&vdbVolumeSelectView);
}

void VolumeToPSView::onOk()
{
	const auto id = vdbVolumeSelectView.getId();
	auto volume = getWorld()->getScenes()->findSceneById<VDBVolumeScene*>(id);

	VDBVolumeConverter converter;
	auto ps = new VDBParticleSystemScene(getWorld()->getNextSceneId(), "VolumeToPS");
	converter.toParticleSystem(*volume, ps);
	ps->getPresenter()->createView(getWorld()->getRenderer());
	getWorld()->getScenes()->addScene(ps);
}