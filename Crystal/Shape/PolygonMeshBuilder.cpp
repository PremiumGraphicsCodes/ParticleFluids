#include "PolygonMeshBuilder.h"
#include "HalfEdge.h"

#include "TriangleMesh.h"

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Plane3d.h"
#include "../Math/Quad3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMeshBuilder::PolygonMeshBuilder() :
	nextId(0)
{}

void PolygonMeshBuilder::build(const std::vector<Triangle3d>& triangles)
{
	std::vector<PolygonVertex> positionNormals;
	std::vector<int> indices;

	int id = 0;
	IndexedList list;
	for (const auto& t : triangles) {
		const auto& vs = t.getVertices();
		const auto& normal = t.getNormal();
		list.vertices.push_back(PolygonVertex(vs[0], normal));
		list.vertices.push_back(PolygonVertex(vs[1], normal));
		list.vertices.push_back(PolygonVertex(vs[2], normal));
		list.indices.push_back({ id++, id++, id++ });
	}
	build(list);
}

void PolygonMeshBuilder::build(const Box3d& box)
{
	//build(box.getPosition(Vector3dd( 0, 0, 0)), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	//build(box.getPosition(Vector3dd( 1, 0, 0)), Vector3df(0, 0, 1), Vector3df(0, 1, 0));

	//faces
}

void PolygonMeshBuilder::build(const Sphere3d& sphere, const int unum, const int vnum)
{
	const auto du = 1.0 / (double)unum;
	const auto dv = 1.0 / (double)vnum;
	std::vector<std::vector<Vertex*>> grid;
	for (double u = 0.0; u < 1.0; u +=du) {
		std::vector<Vertex*> vs;
		for (double v = 0.0; v < 1.0; v+=dv) {
			const auto& p = sphere.getPosition(u, v);
			const auto& n = sphere.getNormal(u, v);
			const Vector2dd texCoord(u, v);
			Vertex* vert = vertexFactory.createVertex(p, n, texCoord);
			vs.push_back(vert);
			this->vertices.push_back(vert);
		}
		grid.push_back(vs);
	}
	for (int i = 0; i < grid.size()-1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			auto e1 = new HalfEdge(grid[i][j], grid[i+1][j] );
			auto e2 = new HalfEdge(grid[i+1][j], grid[i][j+1] );
			auto e3 = new HalfEdge(grid[i][j+1], grid[i][j]);
			auto f1 = new Face(e1, e2, e3);
			//assert(f1->getArea() > 0.0);
			faces.push_back(f1);
			auto e4 = new HalfEdge(grid[i][j+1], grid[i+1][j]);
			auto e5 = new HalfEdge(grid[i+1][j], grid[i+1][j+1]);
			auto e6 = new HalfEdge(grid[i+1][j+1], grid[i][j+1]);
			auto f2 = new Face(e4, e5, e6);
			//assert(f2->getArea() > 0.0);
			faces.push_back(f2);
		}
	}
}

void PolygonMeshBuilder::build(const Quad3d& quad)
{
	const auto& normal = quad.getNormal();

	IndexedList list;
	PolygonVertex v0(quad.getPosition(0, 0), normal, Vector2dd(0, 0));
	PolygonVertex v1(quad.getPosition(1, 0), normal, Vector2dd(1, 0));
	PolygonVertex v2(quad.getPosition(1, 1), normal, Vector2dd(1, 1));
	PolygonVertex v3(quad.getPosition(0, 1), normal, Vector2dd(0, 1));

	list.vertices.push_back(v0);
	list.vertices.push_back(v1);
	list.vertices.push_back(v2);
	list.vertices.push_back(v3);

	list.indices.push_back({ 0,1,3 });
	list.indices.push_back({ 3,1,2 });

	build(list);
	//vertices.push_back(new Ver)
}

void PolygonMeshBuilder::build(const TriangleMesh& mesh)
{
	const auto& fs = mesh.getFaces();
	IndexedList list;
	int id = 0;
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		std::vector<Vertex*> vss;
		for (auto v : vs) {
			PolygonVertex pn(v, normal);
			list.vertices.push_back(pn);
		}
		list.indices.push_back({ id++, id++, id++ });
	}
	build(list);
}

void PolygonMeshBuilder::build(const PolygonMeshBuilder::IndexedList& list)
{
	std::vector<Vertex*> vs;
	for (const auto& pn : list.vertices) {
		auto v = vertexFactory.createVertex(pn.position, pn.normal);
		vs.push_back(v);
		vertices.push_back(v);
	}
	for (const auto& indices : list.indices) {
		const auto v1 = vs[indices[0]];
		const auto v2 = vs[indices[1]];
		const auto v3 = vs[indices[2]];
		auto e1 = new HalfEdge(v1, v2);
		auto e2 = new HalfEdge(v2, v3);
		auto e3 = new HalfEdge(v3, v1);

		faces.push_back(new Face(e1, e2, e3));
	}
}

PolygonMesh* PolygonMeshBuilder::getPolygonMesh() const
{
	return new PolygonMesh(vertices, faces);
}
