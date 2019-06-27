#include "ObjectIdViewModel.h"
#include "Repository.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void ObjectIdViewModel::add(Scene& objects)
{
	const auto& particleSystems = objects.getParticleSystems()->getObjects();
	for (auto ps : particleSystems) {
		add(*ps);
	}
	/*
	const auto& wires = objects.getWireFrames()->getObjects();
	for (auto wf : wires) {
		add(*wf);
	}
	*/
	const auto& polygons = objects.getFactory()->getObjects();
	for (auto p : polygons) {
		add(*p);
	}
}

void ObjectIdViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointIdBuffer.add(pos, c, size);
}

void ObjectIdViewModel::add(const ParticleSystemScene& object)
{
	const auto objectId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	int particleId = 0;
	for (auto p : particles) {
		Graphics::DrawableID did(objectId, particleId++);
		pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size);
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
