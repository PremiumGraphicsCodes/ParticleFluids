#pragma once

#include "ParticleSystemObject.h"
#include <list>

namespace Crystal {
	namespace UI {

class ParticleSystemObjectRepository
{
public:
	ParticleSystemObjectRepository() :
		nextId(1)
	{}

	~ParticleSystemObjectRepository();

	void clear();

	int addObject(const std::vector<Math::Vector3df>& positions, const Graphics::ColorRGBAf& color, const float size, const std::string& name);

	std::list<ParticleSystemObject> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

private:
	int nextId;
	std::list<ParticleSystemObject> objects;
};

	}
}