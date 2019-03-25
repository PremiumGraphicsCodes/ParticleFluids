#include "ObjectViewModel.h"
#include "Repository.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ObjectViewModel::add(ObjectRepository& objects)
{
	const auto& particleSystems = objects.getParticleSystems()->getObjects();
	for (auto ps : particleSystems) {
		add(*ps);
	}
	const auto& wires = objects.getWireFrames()->getObjects();
	for (const auto& w : wires) {
		add(w);
	}
	const auto& polygons = objects.getPolygonMeshes()->getObjects();
	for (auto p : polygons) {
		add(*p);
	}
}

void ObjectViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointBuffer.add(pos, c, size);
}

void ObjectViewModel::add(const ParticleSystemObject& object)
{
	if (!object.isVisible()) {
		return;
	}
	const auto particleSystemId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	for (auto p : particles) {
		pointBuffer.add( p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
}

void ObjectViewModel::add(const WireFrameObject& object)
{
	if (!object.isVisible()) {
		return;
	}
	const auto& lines = object.getShape()->getLines();
	const auto& color = object.getAttribute().color;
	int index = 0;
	for (const auto& l : lines) {
		lineBuffer.add(l.getStart(), color, index++);
		lineBuffer.add(l.getEnd(), color, index++);
	}
}

void ObjectViewModel::add(const PolygonMeshObject& object)
{
	if (!object.isVisible()) {
		return;
	}
	auto material = object.getMaterial();
	TriangleBuffer bf;
	bf.add(*object.getShape(), material);
	triangleBuffers.push_back(bf);

	/*
	const auto& vertices =  object.getShape()->getVertices();
	for (auto l : vertices) {
		triangleBuffer.add(*object.getShape());
	}
	*/
}
