#include "IntersectionButton.h"

#include "../CrystalAlgo/IntersectionAlgo.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Shape;
using namespace Crystal::Model;
using namespace Crystal::UI;
using namespace Crystal::Algo;

IntersectionButton::IntersectionButton(Repository* model, Canvas* canvas) :
	IPopupButton("Intersection", model, canvas),
	mesh1("Mesh1", model, canvas),
	mesh2("Mesh2", model, canvas),
	tolerance("Tolerance", 1.0e-12)
{
}

void IntersectionButton::onShow()
{
	mesh1.show();
	mesh2.show();
}

void IntersectionButton::onOk()
{
	auto obj1 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(mesh1.getId());
	auto obj2 = getModel()->getObjects()->getPolygonMeshes()->findObjectById(mesh2.getId());
	if (obj1 == nullptr || obj2 == nullptr) {
		return;
	}

	IntersectionAlgo algo;
	const auto isFound = algo.calculateIntersection(*obj1->getShape(),*obj2->getShape(), tolerance.getValue());
	if (isFound) {
		const auto& intersections = algo.getIntersections();
		std::vector<Math::Vector3df> positions;
		for (const auto& i : intersections) {
			const auto& p = i.position;
			positions.push_back(p);
		}
		ParticleAttribute attr;
		attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		getModel()->getObjects()->getParticleSystems()->addObject(positions, attr, "intersections");
		getCanvas()->setViewModel(getModel()->toViewModel());
	}
}

void IntersectionButton::onCancel()
{
}

