#pragma once

#include "PolygonMesh.h"
#include "../Util/UnCopyable.h"
#include "../Math/ISurface3d.h"

namespace Crystal {
	namespace Math {
		class Box3d;
		class Sphere3d;
		class Triangle3d;
		class Quad3d;
	}
	namespace Scene {

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Box3d& box);

	void add(const Math::ISurface3d& sphere, const int udiv, const int vdiv);

	void add(const Math::Quad3d& quad);

	//void add(const TriangleMesh& mesh);

	PolygonMesh* getPolygonMesh();

private:
	void add(const int v0, const int v1, const int v2, const int v3);

	PolygonMesh* polygonMesh;
};

	}
}