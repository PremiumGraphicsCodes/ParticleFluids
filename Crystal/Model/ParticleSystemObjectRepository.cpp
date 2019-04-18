#include "ParticleSystemObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

ParticleSystemObjectRepository::ParticleSystemObjectRepository(const ObjectIdProvider& idProvider) :
	IObjectRepository(idProvider),
	nextId(1)
{}

ParticleSystemObjectRepository::~ParticleSystemObjectRepository()
{
	clear();
}

void ParticleSystemObjectRepository::clear()
{
	for (auto p : objects) {
		delete p->getShape();
		delete p;
	}
	objects.clear();
}

int ParticleSystemObjectRepository::addObject(const Vector3df& position, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	particles->add(position, attribute);
	objects.push_back(new ParticleSystemObject(nextId++, name, particles));
	return objects.back()->getId();
}

int ParticleSystemObjectRepository::addObject(const std::vector<Vector3df>& positions, const ParticleAttribute& attribute, const std::string& name)
{
	auto particles = new Shape::ParticleSystem<ParticleAttribute>();
	for (const auto& p : positions) {
		particles->add(p, attribute);
	}
	objects.push_back(new ParticleSystemObject(nextId++, name, particles));
	return objects.back()->getId();
}

ParticleSystemObject* ParticleSystemObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(objects), std::cend(objects), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(objects)) {
		return nullptr;
	}
	return *iter;
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
		const auto& particles = ps->getShape()->getParticles();
		for (const auto& p : particles) {
			positions.push_back(p->getPosition());
		}
	}
	return positions;
}

bool ParticleSystemObjectRepository::exists(const int id) const
{
	auto iter = std::find_if(objects.begin(), objects.end(), [=](auto object) { return object->getId() == id; });
	return iter != objects.end();
}

/*
ParticleSystemObject* ParticleSystemObjectRepository::findObjectById(const int id) const
{
	assert(exists(id));
	auto iter = std::find_if(objects.begin(), objects.end(), [=](auto object) { return object->getId() == id; } );
	return *iter;
}
*/

Particle<ParticleAttribute>* ParticleSystemObjectRepository::findParticleById(const int parentId, const int childId) const
{
	if (!exists(parentId)) {
		return nullptr;
	}
	auto object = findObjectById(parentId);
	const auto& particles = object->getShape()->getParticles();
	return particles[childId];
}