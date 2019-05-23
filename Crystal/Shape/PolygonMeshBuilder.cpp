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

PolygonMeshBuilder::PolygonMeshBuilder()
{}

PolygonMeshBuilder::PolygonMeshBuilder(VertexFactory&& vertexFactory) :
	vertexFactory(std::move(vertexFactory))
{
}

void PolygonMeshBuilder::add(const Triangle3d& triangle)
{
	const auto& vs = triangle.getVertices();
	const auto& normal = triangle.getNormal();
	auto v0 = vertexFactory.createVertex(vs[0], normal);
	auto v1 = vertexFactory.createVertex(vs[1], normal);
	auto v2 = vertexFactory.createVertex(vs[2], normal);
	faceIndices.push_back({ v0,v1,v2 });
}

void PolygonMeshBuilder::add(const Box3d& box)
{
	//build(box.getPosition(Vector3dd( 0, 0, 0)), Vector3dd(1, 0, 0), Vector3dd(0, 1, 0));
	//build(box.getPosition(Vector3dd( 1, 0, 0)), Vector3df(0, 0, 1), Vector3df(0, 1, 0));

	//faces
}

void PolygonMeshBuilder::add(const Sphere3d& sphere, const int unum, const int vnum)
{
	const auto du = 1.0 / (double)unum;
	const auto dv = 1.0 / (double)vnum;
	std::vector<std::vector<int>> grid;
	for (double u = 0.0; u < 1.0; u +=du) {
		std::vector<int> vs;
		for (double v = 0.0; v < 1.0; v+=dv) {
			const auto& p = sphere.getPosition(u, v);
			const auto& n = sphere.getNormal(u, v);
			const Vector2dd texCoord(u, v);
			const auto id = vertexFactory.createVertex(p, n, texCoord);
			vs.push_back(id);
		}
		grid.push_back(vs);
	}
	for (int i = 0; i < grid.size()-1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			std::array<int, 3> f1{ grid[i][j], grid[i + 1][j], grid[i][j + 1] };
			std::array<int, 3> f2{ grid[i][j + 1], grid[i + 1][j], grid[i + 1][j + 1] };
			faceIndices.push_back(f1);
			faceIndices.push_back(f2);
		}
	}
}

void PolygonMeshBuilder::add(const Quad3d& quad)
{
	const auto& normal = quad.getNormal();

	auto v0 = vertexFactory.createVertex(quad.getPosition(0, 0), normal, Vector2dd(0, 0));
	auto v1 = vertexFactory.createVertex(quad.getPosition(1, 0), normal, Vector2dd(1, 0));
	auto v2 = vertexFactory.createVertex(quad.getPosition(1, 1), normal, Vector2dd(1, 1));
	auto v3 = vertexFactory.createVertex(quad.getPosition(0, 1), normal, Vector2dd(0, 1));

	faceIndices.push_back({ v0,v1,v3 });
	faceIndices.push_back({ v3,v1,v2 });
}

void PolygonMeshBuilder::add(const TriangleMesh& mesh)
{
	const auto& fs = mesh.getFaces();
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		std::array<int,3> ids;
		for (int i = 0; i < 3; ++i ) {
			ids[i] = vertexFactory.createVertex(vs[i], normal);
		}
		faceIndices.push_back( ids );
	}
}

void PolygonMeshBuilder::build()
{
	for (const auto& indices : faceIndices) {
		build(indices);
	}
}

void PolygonMeshBuilder::build(const std::array<int, 3>& indices)
{
	const auto& vertices = vertexFactory.getVertices();

	const auto v1 = vertices[indices[0]];
	const auto v2 = vertices[indices[1]];
	const auto v3 = vertices[indices[2]];
	auto e1 = new HalfEdge(v1, v2);
	auto e2 = new HalfEdge(v2, v3);
	auto e3 = new HalfEdge(v3, v1);

	faces.push_back(new Face(e1, e2, e3));
}


PolygonMesh* PolygonMeshBuilder::getPolygonMesh() const
{
	return new PolygonMesh(vertexFactory.getVertices(), faces);
}
