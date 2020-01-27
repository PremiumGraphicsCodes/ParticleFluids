#include "IntersectionView.h"

#include "../CrystalAlgo/IntersectionAlgo.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo;

IntersectionView::IntersectionView(World* model, Canvas* canvas) :
	IOkCancelView("Intersection", model, canvas),
	mesh1("Mesh1", model, canvas),
	mesh2("Mesh2", model, canvas),
	tolerance("Tolerance", 1.0e-12)
{
}

void IntersectionView::onShow()
{
	mesh1.show();
	mesh2.show();
}

void IntersectionView::onOk()
{
	auto repository = getWorld();
	auto obj1 = repository->getObjects()->findSceneById<PolygonMeshScene*>(mesh1.getId());
	auto obj2 = repository->getObjects()->findSceneById<PolygonMeshScene*>(mesh2.getId());
	if (obj1 == nullptr || obj2 == nullptr) {
		return;
	}

	IntersectionAlgo algo;
	const auto isFound = algo.calculateIntersection(*obj1->getShape(),*obj2->getShape(), tolerance.getValue());
	if (isFound) {
		const auto& intersections = algo.getIntersections();
		std::vector<Math::Vector3dd> positions;
		for (const auto& i : intersections) {
			const auto& p = i.position;
			positions.push_back(p);
		}
		ParticleAttribute attr;
		attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attr.size = 1.0f;
		repository->getSceneFactory()->createParticleSystemScene(positions, attr, "intersections");
		getWorld()->updateViewModel();
	}
}

