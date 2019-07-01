#include "ObjectViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void ObjectViewModel::add(Scene& objects)
{
	const auto& particleSystems = objects.getFactory()->getParticleSystems();
	for (auto ps : particleSystems) {
		ps->addViewModel(*this);
	}
	const auto& wires = objects.getFactory()->getWireFrames();
	for (const auto& w : wires) {
		w->addViewModel(*this);
	}
	const auto& polygons = objects.getFactory()->getPolygonMeshes();
	for (auto p : polygons) {
		add(*p);
	}
	const auto& lights = objects.getFactory()->getLights();
	for (auto l : lights) {
		l->addViewModel(*this);
	}
}


void ObjectViewModel::add(const PolygonMeshScene& object)
{
	if (!object.isVisible()) {
		return;
	}

	TriangleBuffer bf(*object.getShape());
	for (const auto& group : object.getShape()->getGroups()) {
		auto mat = object.getMaterial();
		if (mat == nullptr) {
			bf.add(group, Material());
		}
		else {
			bf.add(group, *(mat->getMaterial()));
		}
	}
	triangleBuffers.push_back(bf);

	/*
	const auto& vertices =  object.getShape()->getVertices();
	for (auto l : vertices) {
		triangleBuffer.add(*object.getShape());
	}
	*/
}

