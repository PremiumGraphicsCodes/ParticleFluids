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

	//explicit PolygonMeshBuilder(VertexFactory&& vertexFactory);

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Box3d& box);

	void add(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void add(const Math::Quad3d& quad);

	void add(const TriangleMesh& mesh);

	PolygonMesh* getPolygonMesh();

private:
	void add(Math::Vector3dd* p0, Math::Vector3dd* p1, Math::Vector3dd* p2, Math::Vector3dd* p3Face, FaceGroup& faceGroup);

	PolygonMesh* polygonMesh;
	int nextFaceId;
};

	}
}