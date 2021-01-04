#include "VolumeToPSView.h"

#include "../VDBConverter/VDBParticleSystem.h"
#include "../VDBConverter/VDBVolumeConverter.h"

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
	auto volume = getWorld()->getScenes()->findSceneById<VDBVolume*>(id);

	VDBVolumeConverter converter;
	VDBParticleSystem* ps = new VDBParticleSystem(getWorld()->getNextSceneId(), "VolumeToPS");
	converter.toParticleSystem(*volume, ps);
	ps->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(ps);
}