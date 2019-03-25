#pragma once

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Box3d.h"
#include "PolygonMesh.h"

namespace Crystal {
	namespace Shape {

class PolygonMeshBuilder
{
public:
	PolygonMeshBuilder() :
		nextId(0),
		nextVertexId(0)
	{}

	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void build(const Math::Vector3dd& start, const Math::Vector3dd& uvec, const Math::Vector3dd& vvec);

	void build(const std::vector<std::pair<Math::Vector3dd, Math::Vector3dd> >& positionNormals, const std::vector<int>& indices);

	PolygonMesh* getPolygonMesh() {
		auto mesh = new PolygonMesh(vertices, faces);
		vertices.clear();
		faces.clear();
		return mesh;
	}

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