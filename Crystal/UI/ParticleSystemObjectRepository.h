#pragma once

#include "IObjectRepository.h"
#include "ParticleSystemObject.h"
#include <list>

namespace Crystal {
	namespace UI {

class ParticleSystemObjectRepository : public IObjectRepository
{
public:
	ParticleSystemObjectRepository() :
		nextId(1)
	{}

	~ParticleSystemObjectRepository();

	void clear() override;

	int addObject(const std::vector<Math::Vector3df>& positions, const Graphics::ColorRGBAf& color, const float size, const std::string& name);

	std::list<ParticleSystemObject> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	int nextId;
	std::list<ParticleSystemObject> objects;
};

	}
}