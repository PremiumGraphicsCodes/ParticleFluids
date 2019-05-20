#pragma once

#include "PolygonMesh.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {
		class Box3d;
		class Sphere3d;
		class Triangle3d;
	}
	namespace Shape {
		class TriangleMesh;

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void build(const std::vector<Math::Triangle3d>& triangles);

	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void build(const Math::Vector3dd& start, const Math::Vector3dd& uvec, const Math::Vector3dd& vvec);

	void build(const std::vector<std::pair<Math::Vector3dd, Math::Vector3dd> >& positionNormals, const std::vector<int>& indices);

	//void build(const std::vector<Math::Vector3dd>& positions, const std::vector<Math::Vector3dd>& normals, const std::vector<std::pair<int, int>>& faceIndices);

	void build(const TriangleMesh& mesh);

	PolygonMesh* getPolygonMesh() const;

private:
	//void buildEdges();

	std::vector<Vertex*> vertices;
	std::list<Face*> faces;
	//std::vector<Vertex*> vertices;
	int nextId;
	int nextVertexId;
};

	}
}