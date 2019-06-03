#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;


PolygonMesh::PolygonMesh(VertexFactory&& vertices, FaceFactory&& faces) :
	vertices(std::move(vertices)),
	faces(std::move(faces))
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

Face* PolygonMesh::findFaceById(const int id)
{
	const auto& fs = faces.getFaces();
	auto iter = std::find_if(fs.begin(), fs.end(), [=](auto f) { return f->getId() == id; });
	if (iter == fs.end()) {
		return nullptr;
	}
	return *iter;
}