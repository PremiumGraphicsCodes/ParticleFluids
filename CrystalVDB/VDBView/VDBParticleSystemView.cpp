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
	//auto ps = vdb.toCrystal();
	//ParticleSystemScene* newScene = new ParticleSystemScene(getWorld()->getNextSceneId(), "", ps);
	//getWorld()->getScenes()->addScene(newScene);
}
