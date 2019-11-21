#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "../Shape/Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

PolygonMesh::PolygonMesh()
{}

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	vertices.clear();
	faces.clear();
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

