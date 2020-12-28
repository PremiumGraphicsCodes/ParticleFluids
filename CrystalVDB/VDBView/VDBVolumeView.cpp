#include "VDBVolumeView.h"

//#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../VDBConverter/VDBVolume.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBVolumeView::VDBVolumeView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas)
{
}

void VDBVolumeView::onOk()
{
	VDBVolume volume;
	volume.setValue({ 0,0,0 }, 10);
	volume.setValue({ 10, 0, 0 }, 10);
	/*
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}
	const auto particles = scene->getShape()->getParticles();
	VDBParticleSystem vdb;
	for (auto p : particles) {
		vdb.add(p->getPosition(), p->getAttribute().size);
	}
	auto ps = vdb.toCrystal();
	ParticleAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 0, 0, 1);
	attr.size = 1.0f;
	auto newShape = std::make_unique<Crystal::Shape::ParticleSystem<Crystal::Scene::ParticleAttribute>>(ps->getPositions(), attr);
	ParticleSystemScene* newScene = new ParticleSystemScene(getWorld()->getNextSceneId(), "Clone", std::move(newShape));
	newScene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(newScene);
	*/
}
