#pragma once

#include "ParticleSystemObject.h"
#include <list>

namespace Crystal {
	namespace UI {

class IObjectRepository
{
public:
	IObjectRepository() :
		nextId(1)
	{}

	virtual ~IObjectRepository() {
		clear();
	};

	virtual void clear() = 0;

	virtual Math::Box3d getBoundingBox() const = 0;

	virtual std::list<Math::Vector3dd> getAllVertices() const = 0;

private:
	int nextId;
};

	}
}