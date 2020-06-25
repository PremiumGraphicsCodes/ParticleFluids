#include "ZOrderSearchView.h"

#include "../CrystalAlgo/SpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo;

ZOrderSearchView::ZOrderSearchView(World* model, Canvas* canvas) :
	IOkCancelView("ZOrderSearch", model, canvas),
	positionButton("Position", model, canvas),
	searchRadius("SearchRadius", 1.0),
	objectButton("Object", model, canvas, SceneType::ParticleSystemScene)
{
}

void ZOrderSearchView::onShow()
{
	positionButton.show();
	searchRadius.show();
	objectButton.show();
}

void ZOrderSearchView::onOk()
{
	/*
	auto object = getModel()->getObjects()->getFactory()->getParticleSystems()->findObjectById(objectButton.getId());
	if (object == nullptr) {
		return;
	}

	SpaceHash space(searchRadius.getValue(), object->getShape()->getParticles().size());
	space.add(*object->getShape());

	const auto& neighbors = space.getNeighbors(positionButton.getPosition());

	std::vector<Vector3dd> positions;
	ParticleAttribute attr;
	attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
	attr.size = 1.0;
	for (auto n : neighbors) {
		positions.push_back(n->getPosition());
	}
	getModel()->getObjects()->getParticleSystems()->addObject(positions, attr, "");
	getCanvas()->setViewModel(getModel()->toViewModel());
	*/
}

