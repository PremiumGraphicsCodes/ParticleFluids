#pragma once

#include "IObjectRepository.h"
#include "ParticleSystemObject.h"
#include <list>

namespace Crystal {
	namespace UI {

class ParticleSystemObjectRepository : public IObjectRepository
{
public:
	ParticleSystemObjectRepository();

	~ParticleSystemObjectRepository();

	void clear() override;

	int addObject(const Math::Vector3df& position, const ParticleAttribute& attribute, const std::string& name);

	int addObject(const std::vector<Math::Vector3df>& positions, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemObject* findObjectById(const int id) const;

	std::list<ParticleSystemObject*> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

	bool exists(const int id) const;

	//ParticleSystemObject* findObjectById(const int id) const;

	Shape::Particle<ParticleAttribute>* findParticleById(const int parentId, const int childId) const;

private:
	int nextId;
	std::list<ParticleSystemObject*> objects;
};

	}
}