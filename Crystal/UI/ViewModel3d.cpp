#include "ViewModel3d.h"
#include "Model.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void ViewModel3d::add(ObjectRepository& objects)
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

void ViewModel3d::add(const Vector3df& pos, const ColorRGBAf& c, const float size)
{
	pointBuffer.add(pos, c, size);
}

void ViewModel3d::add(const ParticleSystemObject& object)
{
	const auto& particles = object.getShape()->getParticles();
	for (auto p : particles) {
		pointBuffer.add( p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
}

void ViewModel3d::add(const WireFrameObject& object)
{
	const auto& lines = object.getShape()->getLines();
	const auto& color = object.getColor();
	int index = 0;
	for (const auto& l : lines) {
		lineBuffer.add(l.getStart(), color, index++);
		lineBuffer.add(l.getEnd(), color, index++);
	}
}

void ViewModel3d::add(const PolygonMeshObject& object)
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


void ViewModel3d::add(const LightObjectRepository& lights)
{
	const auto& ls = lights.getLights();
	for (const auto& l : ls) {
		auto ll = l.getLight();
		lightBuffer.add(*ll);
	}
}

void ViewModel3d::add(const MateriaObjectRepository& materials)
{
	const auto& ms = materials.getMaterials();
	for (const auto& m : ms) {
		auto mm = m.getMaterial();
		materialBuffer.add(*mm);
	}
}
