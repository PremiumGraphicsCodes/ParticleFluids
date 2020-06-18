#pragma once

#include "TriangleMesh.h"
#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Math {
		class Triangle3d;
		class Quad3d;
		class Box3d;
		class Sphere3d;
		class Cone3d;
	}
	namespace Shape {

class TriangleMeshBuilder : private UnCopyable
{
public:
	TriangleMeshBuilder();

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Quad3d& quad);

	void add(const Math::Box3d& box);

	/*
	void add(const Math::Sphere3d& sphere, const int unum, const int vnum);

	void add(const Math::Cone3d& cone, int unum);
	*/

	std::unique_ptr<TriangleMesh> build();

private:
	std::vector<TriangleFace> faces;
};

	}
}