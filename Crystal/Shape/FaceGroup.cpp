#include "FaceGroup.h"

using namespace Crystal::Shape;

bool FaceGroup::has(Face* f) const
{
	if (faces.empty()) {
		return false;
	}
	auto iter = std::find(faces.cbegin(), faces.cend(), f);
	return iter != faces.cend();
}
