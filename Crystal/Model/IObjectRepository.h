#pragma once

#include "../Util/UnCopyable.h"
#include "ParticleSystemObject.h"
#include <list>

namespace Crystal {
	namespace Model {

class IObjectRepository : private UnCopyable
{
public:
	IObjectRepository()// :
		//nextId(1)
	{}

	virtual ~IObjectRepository() {};

	virtual void clear() = 0;

	virtual Math::Box3d getBoundingBox() const = 0;

	virtual std::list<Math::Vector3dd> getAllVertices() const = 0;

protected:
	//int getNextId() { return nextId++; }

private:
	//int nextId;
};

	}
}