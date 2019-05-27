#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;


PolygonMesh::PolygonMesh(VertexFactory&& vertices, const std::list<Face*>& faces) :
	vertices(std::move(vertices)),
	faces(faces)
{}

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	vertices.clear();
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}

void PolygonMesh::add(Face* f)
{
	faces.push_back(f);
}

bool PolygonMesh::has(Face* f)
{
	return std::find(faces.begin(), faces.end(), f) != faces.end();
}

bool PolygonMesh::has(HalfEdge* e)
{
	const auto& edges = getEdges();
	return std::find(edges.begin(), edges.end(), e) != edges.end();
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

std::list<HalfEdge*> PolygonMesh::getEdges() const
{
	std::list<HalfEdge*> edges;
	for (auto f : faces) {
		auto es = f->getEdges();
		edges.insert(edges.end(), es.begin(), es.end());
	}
	edges.sort();
	edges.unique();
	return edges;
}

void PolygonMesh::remove(Face* f)
{
	faces.remove(f);
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