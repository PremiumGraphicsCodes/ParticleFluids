#include "ParticleSystemObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

ParticleSystemObjectRepository::ParticleSystemObjectRepository() :
	nextId(1)
{}

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

int ParticleSystemObjectRepository::addObject(const Vector3df& position, const ColorRGBAf& color, const float size, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	ParticleAttribute attr;
	attr.color = color;
	attr.size = size;
	particles->add(position, attr);
	objects.push_back(ParticleSystemObject(nextId++, name, particles));
	return objects.back().getId();
}

int ParticleSystemObjectRepository::addObject(const std::vector<Vector3df>& positions, const ColorRGBAf& color, const float size, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		ParticleAttribute attr;
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

bool ParticleSystemObjectRepository::exists(const int id) const
{
	auto iter = std::find_if(objects.begin(), objects.end(), [=](auto object) { return object.getId() == id; });
	return iter != objects.end();
}

ParticleSystemObject ParticleSystemObjectRepository::findObjectById(const int id) const
{
	assert(exists(id));
	auto iter = std::find_if(objects.begin(), objects.end(), [=](auto object) { return object.getId() == id; } );
	return *iter;
}

Particle<ParticleAttribute>* ParticleSystemObjectRepository::findParticleById(const int parentId, const int childId) const
{
	if (!exists(parentId)) {
		return nullptr;
	}
	auto object = findObjectById(parentId);
	const auto& particles = object.getShape()->getParticles();
	return particles[childId];
}