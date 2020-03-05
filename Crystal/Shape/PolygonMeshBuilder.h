#pragma once

#include "PolygonMesh.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {
		class Triangle3d;
		class Quad3d;
		class Box3d;
		class Sphere3d;
		class Cone3d;
	}
	namespace Shape {

class PolygonMeshBuilder : private UnCopyable
{
public:
	PolygonMeshBuilder();

	void add(const Math::Triangle3d& triangle);

	void add(const Math::Quad3d& quad);

	void add(const Math::Box3d& box);

	void add(const Math::Sphere3d& sphere, const int unum, const int vnum);

	void add(const Math::Cone3d& cone, int unum);

	std::unique_ptr<PolygonMesh> build();

	int createPosition(const Math::Vector3dd& v);

	int createNormal(const Math::Vector3dd& v);

	int createTexCoord(const Math::Vector2dd& v);

	int createVertex(const int positionId, const int normalId = -1, const int texCoordId = -1);

	int createFace(int v0, int v1, int v2);

	void createFaces(int v0, int v1, int v2, int v3);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

	std::vector<Math::Vector3dd> getNormals() const { return normals; }

	std::vector<Math::Vector2dd> getTexCoords() const { return texCoords; }

	std::vector<Vertex> getVertices() const { return vertices; }

	std::vector<Face> getFaces() const { return faces; }

private:
	void add(const int v0, const int v1, const int v2, const int v3);

	Math::Vector3dd calculateNormal(const int v0, const int v1, const int v2);

	std::vector<Math::Vector3dd> positions;
	std::vector<Math::Vector3dd> normals;
	std::vector<Math::Vector2dd> texCoords;

	std::vector<Vertex> vertices;
	std::vector<Face> faces;

	int nextVertexId;
	int nextFaceId;
};

	}
}