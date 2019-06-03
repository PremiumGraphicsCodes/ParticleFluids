#pragma once

#include "PolygonMesh.h"
#include "VertexFactory.h"
#include "FaceFactory.h"
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

	std::vector<Math::Vector3dd*> getPositions() const { return vertexFactory.getPositions(); }

	std::vector<Math::Vector3dd*> getNormals() const { return vertexFactory.getNormals(); }

	std::vector<Math::Vector2dd*> getTexCoords() const { return vertexFactory.getTexCoords(); }

	VertexFactory* getVertexFactory() { return &vertexFactory; }

	FaceFactory* getFaceFactory() { return &faceFactory; }

	int pushCurrentFaceGroup(int attributeId = -1) { return faceFactory.pushCurrentGroup(attributeId); }

private:
	void add(Math::Vector3dd* p0, Math::Vector3dd* p1, Math::Vector3dd* p2, Math::Vector3dd* p3);

	VertexFactory vertexFactory;
	FaceFactory faceFactory;
};

	}
}