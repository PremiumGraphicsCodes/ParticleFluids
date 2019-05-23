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
	nextId(0),
	nextVertexId(0)
{}

void PolygonMeshBuilder::build(const std::vector<Triangle3d>& triangles)
{
	std::vector<PositionNormal> positionNormals;
	std::vector<int> indices;

	int id = 0;
	IndexedList list;
	for (const auto& t : triangles) {
		const auto& vs = t.getVertices();
		const auto& normal = t.getNormal();
		list.positionNormals.push_back(PositionNormal(vs[0], normal));
		list.positionNormals.push_back(PositionNormal(vs[1], normal));
		list.positionNormals.push_back(PositionNormal(vs[2], normal));
		list.indices.push_back(id++);
		list.indices.push_back(id++);
		list.indices.push_back(id++);
	}
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
			VertexAttr attr;
			attr.id = nextVertexId++;
			attr.normal = sphere.getNormal(u,v);
			attr.texCoord = Vector2df(u, v);
			Vertex* vert = new Vertex(sphere.getPosition(u, v), attr);
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

	VertexAttr attr;
	attr.id = nextVertexId++;
	attr.normal = normal;
	attr.texCoord = Vector2df(0, 0);
	auto v0 = new Vertex(quad.getPosition(0,0), attr);
	attr.id = nextVertexId++;
	attr.texCoord = Vector2df(1, 0);
	auto v1 = new Vertex(quad.getPosition(1,0), attr);
	attr.id = nextVertexId++;
	attr.texCoord = Vector2df(0, 1);
	auto v2 = new Vertex(quad.getPosition(1,1), attr);
	attr.id = nextVertexId++;
	attr.texCoord = Vector2df(1, 1);
	auto v3 = new Vertex(quad.getPosition(0,1), attr);
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	auto e1 = new HalfEdge(v0, v1);
	auto e2 = new HalfEdge(v1, v2);
	auto e3 = new HalfEdge(v2, v0);
	faces.push_back(new Face(e1, e2, e3));

	auto e4 = new HalfEdge(v2, v1);
	auto e5 = new HalfEdge(v1, v3);
	auto e6 = new HalfEdge(v3, v2);
	faces.push_back(new Face(e4, e5, e6));

	//vertices.push_back(new Ver)
}

void PolygonMeshBuilder::build(const PolygonMeshBuilder::IndexedList& list)
{
	std::vector<Vertex*> vs;
	for (const auto& pn : list.positionNormals) {
		const auto& position = pn.position;
		VertexAttr attr;
		attr.normal = pn.normal;
		attr.id = nextVertexId++;
		auto v = new Vertex(position, attr);
		vs.push_back(v);
		vertices.push_back(v);
	}
	for (size_t i = 0; i < list.indices.size(); i+=3) {
		const auto v1 = vs[ list.indices[i+0] ];
		const auto v2 = vs[ list.indices[i+1] ];
		const auto v3 = vs[ list.indices[i+2] ];
		auto e1 = new HalfEdge(v1, v2);
		auto e2 = new HalfEdge(v2, v3);
		auto e3 = new HalfEdge(v3, v1);

		faces.push_back(new Face(e1, e2, e3));
	}
}

void PolygonMeshBuilder::build(const TriangleMesh& mesh)
{
	const auto& fs = mesh.getFaces();
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		std::vector<Vertex*> vss;
		for (auto v : vs) {
			VertexAttr attr;
			attr.normal = normal;
			attr.id = nextVertexId++;
			vss.push_back( new Vertex(v, attr) );
		}
		for (auto v : vss) {
			vertices.push_back(v);
		}
		auto e1 = new HalfEdge(vss[0], vss[1]);
		auto e2 = new HalfEdge(vss[1], vss[2]);
		auto e3 = new HalfEdge(vss[2], vss[0]);

		faces.push_back(new Face(e1, e2, e3));
	}
}


PolygonMesh* PolygonMeshBuilder::getPolygonMesh() const
{
	return new PolygonMesh(vertices, faces);
}
