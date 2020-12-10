#include "VDBParticleSystemView.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../VDBConverter/VDBParticleSystem.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBParticleSystemView::VDBParticleSystemView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	particleSystemSelectView("ParticleSystem", model, canvas)
{
	add(&particleSystemSelectView);
}

void VDBParticleSystemView::onOk()
{
	auto id = particleSystemSelectView.getId();
	auto scene = getWorld()->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return;
	}
	const auto positions = scene->getShape()->getPositions();
	VDBParticleSystem vdb;
	vdb.fromCrystal(*scene->getShape());
	auto ps = vdb.toCrystal();
	ParticleAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1, 0, 0, 1);
	attr.size = 1.0f;
	auto newShape = std::make_unique<Crystal::Shape::ParticleSystem<Crystal::Scene::ParticleAttribute>>(ps->getPositions(), attr);
	ParticleSystemScene* newScene = new ParticleSystemScene(getWorld()->getNextSceneId(), "Clone",std::move(newShape));
	newScene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	getWorld()->getScenes()->addScene(newScene);
}
