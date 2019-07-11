#pragma once

#include <list>
#include "Face.h"

namespace Crystal {
	namespace Shape {

struct FaceGroup
{
	FaceGroup() :
		id(-1),
		attributeId(-1)
	{}

	explicit FaceGroup(const int id) :
		id(id),
		attributeId(-1)
	{}

	std::list<Face> faces;
	int id;
	int attributeId;

	//bool has(Face f) const;
};

	}
}