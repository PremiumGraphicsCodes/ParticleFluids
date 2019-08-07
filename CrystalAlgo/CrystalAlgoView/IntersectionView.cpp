#include "IntersectionView.h"

#include "../CrystalAlgo/IntersectionAlgo.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Algo;

IntersectionView::IntersectionView(RootScene* model, Canvas* canvas) :
	IOkCancelView("Intersection", model, canvas),
	mesh1("Mesh1", model, canvas),
	mesh2("Mesh2", model, canvas),
	tolerance("Tolerance", 1.0e-12)
{
}

void IntersectionView::show()
{
	mesh1.show();
	mesh2.show();
}

void IntersectionView::onOk()
{
	auto repository = getRepository();
	auto obj1 = static_cast<PolygonMeshScene*>( repository->getObjects()->findSceneById(mesh1.getId()) );
	auto obj2 = static_cast<PolygonMeshScene*>( repository->getObjects()->findSceneById(mesh2.getId()) );
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
		repository->getObjectFactory()->createParticleSystemScene(positions, attr, "intersections");
		getCanvas()->setViewModel(repository->toViewModel());
	}
}

