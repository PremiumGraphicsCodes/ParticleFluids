#include "SceneIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void SceneIdViewModel::add(Scene& objects)
{
	const auto& particleSystems = objects.getFactory()->getParticleSystems();
	for (auto ps : particleSystems) {
		ps->addViewModel(*this);
	}
	const auto& wires = objects.getFactory()->getWireFrames();
	for (auto wf : wires) {
		wf->addViewModel(*this);
	}
	const auto& polygons = objects.getFactory()->getPolygonMeshes();
	for (auto p : polygons) {
		add(*p);
	}
}

void SceneIdViewModel::add(const PolygonMeshScene& object)
{
	const auto objectId = object.getId();
	const auto& faces = object.getShape()->getFaces();
	int childId = 0;
	int index = 0;
	for (auto f : faces) {
		Graphics::DrawableID did(objectId, childId++);
		const auto& idColor = did.toColor();
		triangleIdBuffer.add(f->getV1()->getPosition(), idColor, index++);
		triangleIdBuffer.add(f->getV2()->getPosition(), idColor, index++);
		triangleIdBuffer.add(f->getV3()->getPosition(), idColor, index++);
	}
}
