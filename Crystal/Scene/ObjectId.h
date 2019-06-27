#pragma once

#include "SceneType.h"

namespace Crystal {
	namespace Model {

class ObjectId
{
public:
	ObjectId(const SceneType& type, const int parentId, const int childId) :
		type(type),
		parentId(parentId),
		childId(childId)
	{}

	SceneType getType() const { return type; }

	int getParentId() const { return parentId; }

	int getChildId() const { return childId; }

private:
	SceneType type;
	int parentId;
	int childId;
};
	}
}