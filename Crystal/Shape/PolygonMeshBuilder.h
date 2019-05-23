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
	struct PositionNormal
	{
		PositionNormal()
		{}

		PositionNormal(const Math::Vector3dd& position, const Math::Vector3dd& normal) :
			position(position),
			normal(normal)
		{}

		PositionNormal(const Math::Vector3dd&& position, const Math::Vector3dd&& normal) :
			position(std::move(position)),
			normal(std::move(normal))
		{}

		Math::Vector3dd position;
		Math::Vector3dd normal;
	};

	struct IndexedList
	{
		IndexedList()
		{}

		IndexedList(const std::vector<PositionNormal>& positionNormals, const std::vector<int>& indices) :
			positionNormals(positionNormals),
			indices(indices)
		{}

		std::vector<PositionNormal> positionNormals;
		std::vector<int> indices;
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