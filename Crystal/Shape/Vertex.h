#ifndef __CRYSTAL_SHAPE_VERTEX_H__
#define __CRYSTAL_SHAPE_VERTEX_H__

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"
#include "../Math/Box3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Shape {

class Vertex
{
public:
	int positionId;
	int normalId;
	int texCoordId;
	int id;
};


class Util {
public:
	static Math::Box3d getBoundingBox(const std::list<Vertex*>& vertices);
};

	}
}
#endif