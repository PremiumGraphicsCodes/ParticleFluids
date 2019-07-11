#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	vertices.clear();
	faceGroups.clear();
}

bool PolygonMesh::has(Vertex* v)
{
	const auto& vertices = getVertices();
	return std::find(vertices.begin(), vertices.end(), v) != vertices.end();
}

std::vector<Vertex*> PolygonMesh::getVertices() const
{
	return vertices.getVertices();
}

Vector3dd PolygonMesh::getCenter() const
{
	Vector3dd center;
	const auto& vs = this->getVertices();
	for (const auto& v : vs) {
		center += v->getPosition() / static_cast<double>(vs.size());
	}
	return center;
}

void PolygonMesh::move(const Vector3dd& v)
{
	const auto& vs = getVertices();
	for (auto& vert : vs) {
		vert->move(v);
	}
}

void PolygonMesh::transform(const Matrix3dd& m)
{
	const auto& vs = vertices.getVertices();
	for (auto p : vs) {
		p->transform(m);
	}
}

void PolygonMesh::transform(const Matrix4dd& m)
{
	const auto& vs = vertices.getVertices();
	for (auto p : vs) {
		p->transform(m);
	}
}

Box3d PolygonMesh::getBoundingBox() const
{
	const auto& vertices = getVertices();

	if (vertices.empty()) {
		return Box3d();
	}

	Box3d bb(vertices.front()->getPosition());
	for (const auto& v : vertices) {
		bb.add(v->getPosition());
	}
	return bb;
}
