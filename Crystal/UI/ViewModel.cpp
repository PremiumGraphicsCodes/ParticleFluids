#include "ViewModel.h"
#include "Model.h"

#include "../Graphics/DrawableId.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ViewModel::add(ObjectRepository& objects)
{
	const auto& particleSystems = objects.getParticleSystems()->getObjects();
	for (const auto& ps : particleSystems) {
		add(ps);
	}
	const auto& wires = objects.getWireFrames()->getObjects();
	for (const auto& w : wires) {
		add(w);
	}
	const auto& polygons = objects.getPolygonMeshes()->getObjects();
	for (const auto& p : polygons) {
		add(p);
	}
}

void ViewModel::add(AppearanceObjectRepository& appearances)
{
	add(*appearances.getLights());
	add(*appearances.getMaterials());
}

void ViewModel::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointBuffer.add(pos, c, size);
}

void ViewModel::add(const ParticleSystemObject& object)
{
	const auto particleSystemId = object.getId();
	const auto& particles = object.getShape()->getParticles();
	int particleId = 1;
	for (auto p : particles) {
		pointBuffer.add( p->getPosition(), p->getAttribute().color, p->getAttribute().size);
		particleId++;
		Graphics::DrawableID did(particleSystemId, particleId++);
//		pointIdBuffer.add(p->getPosition(), did.toColor(), p->getAttribute().size());
	}
}

void ViewModel::add(const WireFrameObject& object)
{
	const auto& lines = object.getShape()->getLines();
	const auto& color = object.getColor();
	int index = 0;
	for (const auto& l : lines) {
		lineBuffer.add(l.getStart(), color, index++);
		lineBuffer.add(l.getEnd(), color, index++);
	}
}

void ViewModel::add(const PolygonMeshObject& object)
{
	auto material = object.getMaterial();
	triangleBuffer.add(*object.getShape(), material);

	/*
	const auto& vertices =  object.getShape()->getVertices();
	for (auto l : vertices) {
		triangleBuffer.add(*object.getShape());
	}
	*/
}


void ViewModel::add(const LightObjectRepository& lights)
{
	const auto& ls = lights.getLights();
	for (const auto& l : ls) {
		auto ll = l.getLight();
		lightBuffer.add(*ll);
	}
}

void ViewModel::add(const MaterialObjectRepository& materials)
{
	const auto& ms = materials.getMaterials();
	for (const auto& m : ms) {
		auto mm = m.getMaterial();
		materialBuffer.add(*mm);
	}
}
