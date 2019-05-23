#pragma once

#include "PolygonMesh.h"
#include "VertexFactory.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {
		class Box3d;
		class Sphere3d;
		class Triangle3d;
		class Quad3d;
	}
	namespace Shape {
		class TriangleMesh;

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Box3d& box);

	void add(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void add(const Math::Quad3d& quad);

	void add(const TriangleMesh& mesh);

	void build();

	PolygonMesh* getPolygonMesh() const;

private:
	VertexFactory vertexFactory;
	std::vector<std::array<int, 3>> faceIndices;
	std::list<Face*> faces;
};

	}
}