#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMesh::PolygonMesh() :
	nextVertexId(0),
	nextFaceId(0)
{}

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	vertices.clear();
	faces.clear();
	nextVertexId = 0;
	nextFaceId = 0;
}

std::vector<Vertex> PolygonMesh::getVertices() const
{
	return vertices;
}

Vector3dd PolygonMesh::getCenter() const
{
	Vector3dd center;
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		const auto p = positions[ v.positionId ];
		center += p / static_cast<double>(vs.size());
	}
	return center;
}

void PolygonMesh::move(const Vector3dd& vec)
{
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		positions[v.positionId] += vec;
	}
}

void PolygonMesh::transform(const Matrix3dd& m)
{
	const auto& vs = vertices;
	for (auto v : vs) {
		auto& p = positions[v.positionId];
		p = p * m;
	}
}

void PolygonMesh::transform(const Matrix4dd& m)
{
	const auto& vs = vertices;
	for (auto v : vs) {
		auto& p = positions[v.positionId];
		p = glm::vec4(p,1.0) * m;
	}
}

Box3d PolygonMesh::getBoundingBox() const
{
	const auto& vertices = getVertices();

	if (vertices.empty()) {
		return Box3d();
	}

	Box3d bb(positions.front());
	for (const auto& p : positions) {
		bb.add(p);
	}
	return bb;
}

int PolygonMesh::createPosition(const Vector3dd& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

int PolygonMesh::createNormal(const Vector3dd& v)
{
	normals.push_back(v);
	return static_cast<int>(normals.size() - 1);
}

int PolygonMesh::createTexCoord(const Vector2dd& v)
{
	texCoords.push_back(v);
	return static_cast<int>(texCoords.size() - 1);
}

int PolygonMesh::createVertex(const int positionId, const int normalId, const int texCoordId)
{
	Vertex v;
	v.positionId = positionId;
	v.normalId = normalId;
	v.texCoordId = texCoordId;
	v.id = nextVertexId++;
	vertices.push_back(v);
	return v.id;
}

int PolygonMesh::createFace(int v0, int v1, int v2)
{
	Face f(v0, v1, v2, nextFaceId++);
	faces.push_back(f);
	return f.getId();
}
