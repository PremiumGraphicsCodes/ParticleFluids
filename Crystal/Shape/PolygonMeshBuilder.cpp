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
	std::vector<std::array<int,3>> indices;

	for (const auto& t : triangles) {
		const auto& vs = t.getVertices();
		const auto& normal = t.getNormal();
		auto v0 = vertexFactory.createVertex(vs[0], normal);
		auto v1 = vertexFactory.createVertex(vs[1], normal);
		auto v2 = vertexFactory.createVertex(vs[2], normal);
		indices.push_back({ v0->getAttr().id, v1->getAttr().id, v2->getAttr().id });
	}
	build(indices);
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

	auto v0 = vertexFactory.createVertex(quad.getPosition(0, 0), normal, Vector2dd(0, 0));
	auto v1 = vertexFactory.createVertex(quad.getPosition(1, 0), normal, Vector2dd(1, 0));
	auto v2 = vertexFactory.createVertex(quad.getPosition(1, 1), normal, Vector2dd(1, 1));
	auto v3 = vertexFactory.createVertex(quad.getPosition(0, 1), normal, Vector2dd(0, 1));

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	const auto i0 = v0->getAttr().id;
	const auto i1 = v1->getAttr().id;
	const auto i2 = v2->getAttr().id;
	const auto i3 = v3->getAttr().id;

	std::vector<std::array<int, 3>> faceIndices;
	faceIndices.push_back({ i0,i1,i3 });
	faceIndices.push_back({ i3,i1,i2 });

	build(faceIndices);
	//vertices.push_back(new Ver)
}

void PolygonMeshBuilder::build(const TriangleMesh& mesh)
{
	const auto& fs = mesh.getFaces();
	std::vector< std::array<int, 3> > indices;
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		std::array<int,3> ids;
		for (int i = 0; i < 3; ++i ) {
			auto vertex = vertexFactory.createVertex(vs[i], normal);
			vertices.push_back(vertex);
			ids[i] = vertex->getAttr().id;
		}
		indices.push_back( ids );
	}
	build(indices);
}

void PolygonMeshBuilder::build(const std::vector<std::array<int,3>>& faceIndices)
{
	for (const auto& indices : faceIndices) {
		const auto v1 = vertices[indices[0]];
		const auto v2 = vertices[indices[1]];
		const auto v3 = vertices[indices[2]];
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
