#include "PolygonMesh.h"

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;


PolygonMesh::PolygonMesh(const std::vector<Vertex*>& vertices, const std::list<Face*>& faces) :
	vertices(vertices),
	faces(faces)
{}

PolygonMesh::~PolygonMesh()
{
	clear();
}

void PolygonMesh::clear()
{
	for (auto v : vertices) {
		delete v;
	}
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
	return vertices;
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

PolygonMesh* PolygonMesh::clone()
{
	return new PolygonMesh(vertices, faces);
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
	for (auto p : vertices) {
		p->transform(m);
	}
}

void PolygonMesh::transform(const Matrix4dd& m)
{
	for (auto p : vertices) {
		p->transform(m);
	}
}

void PolygonMesh::updateNormals()
{
	std::list<Face*> fs;
	for (auto f : faces) {
		if (f->getArea() > 1.0e-6) {
			fs.push_back(f);
		}
	}

	for (auto f : fs) {
		for (auto v : f->getVertices()) {
			v->setNormal(Vector3df(0, 0, 0));
		}
	}
	for (auto f : fs) {
		const auto area = f->getArea() * 1.0e+6;
		//assert(area > 0);
		//assert(area > 1.0e-1);
		const auto& normal = f->getNormal();
		for (auto v : f->getVertices()) {
			v->setNormal(v->getNormal() + area * normal);
		}
	}
	for (auto f : fs) {
		for (auto v : f->getVertices()) {
			auto n = v->getNormal();
			v->setNormal(glm::normalize( n ));
		}
	}
}