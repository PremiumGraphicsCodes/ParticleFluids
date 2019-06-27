#pragma once

#include "IObjectRepository.h"
#include "ParticleSystemScene.h"
#include <list>

namespace Crystal {
	namespace Model {

class ParticleSystemObjectRepository : public IObjectRepository
{
public:
	explicit ParticleSystemObjectRepository(SceneIdProvider& idProvider);

	~ParticleSystemObjectRepository();

	void clear() override;

	int addObject(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	int addObject(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	int addObject(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	ParticleSystemScene* findObjectById(const int id) const;

	std::list<ParticleSystemScene*> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

	bool exists(const int id) const;

	//ParticleSystemObject* findObjectById(const int id) const;

	Shape::Particle<ParticleAttribute>* findParticleById(const int parentId, const int childId) const;

private:
	std::list<ParticleSystemScene*> objects;
};

	}
}