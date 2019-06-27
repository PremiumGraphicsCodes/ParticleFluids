#include "ObjectViewModel.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;

void ObjectViewModel::add(Scene& objects, MaterialObjectRepository& materials)
{
	const auto& particleSystems = objects.getFactory()->getParticleSystems();
	for (auto ps : particleSystems) {
		add(*ps);
	}
	const auto& wires = objects.getFactory()->getWireFrames();
	for (const auto& w : wires) {
		add(*w);
	}
	const auto& polygons = objects.getFactory()->getPolygonMeshes();
	for (auto p : polygons) {
		add(*p, materials);
	}
}

void ObjectViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointBuffer.add(pos, c, size);
}

void ObjectViewModel::add(const ParticleSystemScene& object)
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

void ObjectViewModel::add(const WireFrameScene& object)
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

void ObjectViewModel::add(const PolygonMeshScene& object, MaterialObjectRepository& materials)
{
	if (!object.isVisible()) {
		return;
	}

	TriangleBuffer bf(*object.getShape());
	for (const auto& group : object.getShape()->getGroups()) {
		auto mat = materials.findObjectById(group.attributeId);
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
