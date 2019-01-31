#include "ParticleSystemObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ParticleSystemObjectRepository::~ParticleSystemObjectRepository()
{
	clear();
}

void ParticleSystemObjectRepository::clear()
{
	for (auto p : objects) {
		delete p.getShape();
	}
	objects.clear();
}

int ParticleSystemObjectRepository::addObject(const std::vector<Vector3df>& positions, const ColorRGBAf& color, const float size, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttr>();
	for (const auto& p : positions) {
		ParticleAttr attr;
		attr.color = color;
		attr.size = size;
		particles->add(p, attr);
	}
	objects.push_back(ParticleSystemObject(nextId++, name, particles));
	return objects.back().getId();
}

Box3d ParticleSystemObjectRepository::getBoundingBox() const
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

std::list<Vector3dd> ParticleSystemObjectRepository::getAllVertices() const
{
	std::list<Vector3dd> positions;
	for (const auto& ps : objects) {
		const auto& particles = ps.getShape()->getParticles();
		for (const auto& p : particles) {
			positions.push_back(p->getPosition());
		}
	}
	return positions;
}
