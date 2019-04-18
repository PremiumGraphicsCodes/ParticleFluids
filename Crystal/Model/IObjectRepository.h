#pragma once

#include "../Math/Box3d.h"
#include "../Util/UnCopyable.h"
#include "ObjectIdProvider.h"
#include <list>

namespace Crystal {
	namespace Model {

class IObjectRepository : private UnCopyable
{
public:
	explicit IObjectRepository(ObjectIdProvider& idProvider) :
		idProvider(idProvider)
	{}

	virtual ~IObjectRepository() {};

	virtual void clear() = 0;

	virtual Math::Box3d getBoundingBox() const = 0;

	virtual std::list<Math::Vector3dd> getAllVertices() const = 0;

	int getNextId() { return idProvider.getNextId(); }

protected:

private:
	ObjectIdProvider& idProvider;
};

	}
}