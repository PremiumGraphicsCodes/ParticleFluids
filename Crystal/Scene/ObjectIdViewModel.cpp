#include "ObjectIdViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void ObjectIdViewModel::add(Scene& objects)
{
	const auto& particleSystems = objects.getFactory()->getParticleSystems();
	for (auto ps : particleSystems) {
		ps->addViewModel(*this);
	}
	const auto& wires = objects.getFactory()->getWireFrames();
	for (auto wf : wires) {
		add(*wf);
	}
	const auto& polygons = objects.getFactory()->getPolygonMeshes();
	for (auto p : polygons) {
		add(*p);
	}
}

void ObjectIdViewModel::add(const WireFrameScene& object)
{
	const auto objectId = object.getId();
	const auto& lines = object.getShape()->getLines();
	int childId = 0;
	int index = 0;
	for (auto l : lines) {
		Graphics::DrawableID did(objectId, childId++);
		lineIdBuffer.add(l.getStart(), did.toColor(), index++);
	}
}

void ObjectIdViewModel::add(const PolygonMeshScene& object)
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
