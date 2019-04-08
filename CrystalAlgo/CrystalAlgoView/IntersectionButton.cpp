#include "IntersectionButton.h"

#include "../CrystalAlgo/IntersectionAlgo.h"
#include "../../Crystal/Shape/WireFrameBuilder.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::Algo;

IntersectionButton::IntersectionButton(Repository* model, Canvas* canvas) :
	IPopupButton("Intersection", model, canvas),
	ray("Ray"),
	plane("Plane"),
	tolerance("Tolerance", 1.0e-12)
{
}

void IntersectionButton::onShow()
{
	ray.show();
	plane.show();
}

void IntersectionButton::onOk()
{
	IntersectionAlgo algo;
	const auto isFound = algo.calculateIntersection(ray.getValue(), plane.getValue(), tolerance.getValue());
	if (isFound) {
		WireFrameBuilder builder;
		builder.build(ray.getValue(), 1.0e+2);
		WireFrameAttribute attr;
		attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
		attr.width = 1.0f;
		getModel()->getObjects()->getWireFrames()->addObject(builder.getWireFrame(), attr, "ray");

		const auto& intersections = algo.getIntersections();
		for (const auto& i : intersections) {
			const auto& p = i.position;
			ParticleAttribute attr;
			attr.color = glm::vec4(1.0, 0.0, 0.0, 0.0);
			attr.size = 100.0f;
			getModel()->getObjects()->getParticleSystems()->addObject(p, attr, "intersection");
			getCanvas()->setViewModel(getModel()->toViewModel());
		}
	}
}

void IntersectionButton::onCancel()
{
}

