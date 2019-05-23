#pragma once

#include "PolygonMesh.h"
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
	struct PolygonVertex
	{
		PolygonVertex()
		{}

		PolygonVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal) :
			position(position),
			normal(normal)
		{}

		PolygonVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal, const Math::Vector2dd& texCoord) :
			position(position),
			normal(normal),
			texCoord(texCoord)
		{}


		Math::Vector3dd position;
		Math::Vector3dd normal;
		Math::Vector2dd texCoord;
	};

	struct IndexedList
	{
		IndexedList()
		{}

		IndexedList(const std::vector<PolygonVertex>& vertices, const std::vector<std::array<int,3>>& indices) :
			vertices(vertices),
			indices(indices)
		{}

		std::vector<PolygonVertex> vertices;
		std::vector<std::array<int,3>> indices;
	};

	PolygonMeshBuilder();

	void build(const std::vector<Math::Triangle3d>& triangles);

	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void build(const Math::Quad3d& quad);

	void build(const IndexedList& list);

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