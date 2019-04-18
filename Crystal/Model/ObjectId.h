#pragma once

#include "ObjectType.h"

namespace Crystal {
	namespace Model {

class ObjectId
{
public:
	ObjectId(const ObjectType& type, const int parentId, const int childId) :
		type(type),
		parentId(parentId),
		childId(childId)
	{}

	ObjectType getType() const { return type; }

	int getParentId() const { return parentId; }

	int getChildId() const { return childId; }

private:
	ObjectType type;
	int parentId;
	int childId;
};
	}
}