#include "ObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ObjectRepository::~ObjectRepository()
{
	clear();
}

void ObjectRepository::clear()
{
	for (auto p : particleSystems) {
		delete p.getShape();
	}
	particleSystems.clear();
	for (auto w : wires) {
		delete w.getShape();
	}
	wires.clear();
	for (auto p : polygonMeshes) {
		delete p.getShape();
	}
	polygonMeshes.clear();
}

int ObjectRepository::addParticleSystem(const std::vector<Vector3df>& positions, const ColorRGBAf& color, const float size, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttr>();
	for (const auto& p : positions) {
		ParticleAttr attr;
		attr.color = color;
		attr.size = size;
		particles->add(p, attr);
	}
	particleSystems.push_back(ParticleSystemObject(nextId++, name, particles));
	return particleSystems.back().getId();
}

int ObjectRepository::addWireFrame(WireFrame* wire, const ColorRGBAf& color, const std::string& name)
{
	wires.push_back(WireFrameObject(nextId++, name, wire, color));
	return wires.back().getId();
}

int ObjectRepository::addPolygonMesh(PolygonMesh* mesh, const Material& material, const std::string& name)
{
	polygonMeshes.push_back(PolygonMeshObject(nextId++, name, mesh, material));
	return polygonMeshes.back().getId();
}

Box3d ObjectRepository::getBoundingBox() const
{
	const auto& vertices = getAllVertices();
	if (vertices.empty()) {
		return Box3d();
	}
	Box3d bb(vertices.front());
	for (const auto& v : vertices) {
		bb.add(v);
	}
	return bb;
}

std::list<Vector3dd> ObjectRepository::getAllVertices() const
{
	std::list<Vector3dd> positions;
	for (const auto& ps : particleSystems) {
		const auto& particles = ps.getShape()->getParticles();
		for (const auto& p : particles) {
			positions.push_back( p->getPosition() );
		}
	}
	for (const auto& ws : wires) {
		const auto& vs = ws.getShape()->getVertices();
		positions.insert(positions.end(), vs.begin(), vs.end());
	}
	for (const auto& ps : polygonMeshes) {
		const auto& vs = ps.getShape()->getVertices();
		for (const auto& p : vs) {
			positions.push_back(p->getPosition());
		}
	}
	return positions;
}
