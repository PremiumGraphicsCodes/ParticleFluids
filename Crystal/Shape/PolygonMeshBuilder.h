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

class VertexFactory : private UnCopyable
{
public:
	VertexFactory() :
		nextId(0)
	{}

	Vertex* createVertex(const Math::Vector3dd& position)
	{
		Shape::VertexAttr attr;
		attr.id = nextId++;
		return new Vertex(position, attr);
	}

	Vertex* createVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal)
	{
		Shape::VertexAttr attr;
		attr.normal = normal;
		attr.id = nextId++;
		return new Vertex(position, attr);
	}

	Vertex* createVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal, const Math::Vector2dd& texCoord)
	{
		Shape::VertexAttr attr;
		attr.normal = normal;
		attr.texCoord = texCoord;
		attr.id = nextId++;
		return new Vertex(position, attr);
	}

private:
	int nextId;
};

class PolygonMeshBuilder : private UnCopyable
{
public:

	PolygonMeshBuilder();

	void build(const std::vector<Math::Triangle3d>& triangles);

	void build(const Math::Box3d& box);

	void build(const Math::Sphere3d& sphere, const int udiv, const int vdiv);

	void build(const Math::Quad3d& quad);

	void build(const std::vector<std::array<int, 3>>& faceIndices);

	void build(const TriangleMesh& mesh);

	PolygonMesh* getPolygonMesh() const;

private:
	VertexFactory vertexFactory;

	std::list<Face*> faces;
	std::vector<Vertex*> vertices;
	int nextId;
};

	}
}