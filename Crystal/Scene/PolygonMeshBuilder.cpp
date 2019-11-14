#include "PolygonMeshBuilder.h"

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Plane3d.h"
#include "../Math/Quad3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

PolygonMeshBuilder::PolygonMeshBuilder() :
	polygonMesh(new PolygonMesh())
{}

void PolygonMeshBuilder::add(const Triangle3d& triangle)
{
	const auto& vs = triangle.getVertices();
	const auto p0 = polygonMesh->createPosition(vs[0]);
	const auto p1 = polygonMesh->createPosition(vs[1]);
	const auto p2 = polygonMesh->createPosition(vs[2]);
	const auto n = polygonMesh->createNormal(triangle.getNormal());
	const auto v0 = polygonMesh->createVertex( p0, n, -1);
	const auto v1 = polygonMesh->createVertex( p1, n, -1);
	const auto v2 = polygonMesh->createVertex( p2, n, -1);
	polygonMesh->createFace( v0, v1, v2 );
}

void PolygonMeshBuilder::add(const Box3d& box)
{
	auto p0 = polygonMesh->createPosition(box.getPosition(0, 0, 0));
	auto p1 = polygonMesh->createPosition(box.getPosition(1, 0, 0));
	auto p2 = polygonMesh->createPosition(box.getPosition(1, 1, 0));
	auto p3 = polygonMesh->createPosition(box.getPosition(0, 1, 0));

	auto p4 = polygonMesh->createPosition(box.getPosition(0, 0, 1));
	auto p5 = polygonMesh->createPosition(box.getPosition(1, 0, 1));
	auto p6 = polygonMesh->createPosition(box.getPosition(1, 1, 1));
	auto p7 = polygonMesh->createPosition(box.getPosition(0, 1, 1));

	add(p0, p1, p2, p3); // front
	add(p7, p6, p5, p4); // back
	add(p3, p2, p6, p7); // top
	add(p0, p1, p5, p4); // bottom
	add(p0, p4, p7, p3); // left
	add(p1, p5, p6, p2); // right
}

void PolygonMeshBuilder::add(const ISurface3d& sphere, const int unum, const int vnum)
{
	const auto du = 1.0 / (double)unum;
	const auto dv = 1.0 / (double)vnum;
	std::vector<std::vector<int>> grid;
	for (double u = 0.0; u < 1.0; u +=du) {
		std::vector<int> vs;
		for (double v = 0.0; v < 1.0; v+=dv) {
			const auto p = polygonMesh->createPosition( sphere.getPosition( u, v) );
			const auto n = polygonMesh->createNormal( sphere.getNormal(u, v) );
			const auto tx = polygonMesh->createTexCoord(Vector2dd( u,v) );
			const auto id = polygonMesh->createVertex(p, n, tx);
			vs.push_back(id);
		}
		grid.push_back(vs);
	}
	for (int i = 0; i < grid.size()-1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			polygonMesh->createFace( grid[i][j], grid[i + 1][j], grid[i][j + 1] );
			polygonMesh->createFace( grid[i][j + 1], grid[i + 1][j], grid[i + 1][j + 1] );
		}
	}
}

void PolygonMeshBuilder::add(const Quad3d& quad)
{
	auto normal = polygonMesh->createNormal( quad.getNormal() );

	auto v00 = polygonMesh->createVertex( polygonMesh->createPosition( quad.getPosition(0, 0) ), normal, polygonMesh->createTexCoord( Vector2dd(0, 0)) );
	auto v01 = polygonMesh->createVertex(polygonMesh->createPosition(quad.getPosition(0, 1)), normal, polygonMesh->createTexCoord(Vector2dd(0, 1)));
	auto v10 = polygonMesh->createVertex( polygonMesh->createPosition( quad.getPosition(1, 0) ), normal, polygonMesh->createTexCoord( Vector2dd(1, 0)) );
	auto v11 = polygonMesh->createVertex( polygonMesh->createPosition( quad.getPosition(1, 1) ), normal, polygonMesh->createTexCoord( Vector2dd(1, 1)) );

	polygonMesh->createFace(v00,v01,v10);
	polygonMesh->createFace(v11,v10,v01);
}

/*
void PolygonMeshBuilder::add(const TriangleMesh& mesh)
{
	const auto& fs = mesh.getFaces();
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		auto n = polygonMesh->createNormal(normal);
		std::array<int,3> ids;
		for (int i = 0; i < 3; ++i ) {
			auto p = polygonMesh->createPosition(vs[i]);
			ids[i] = polygonMesh->createVertex(p, n);
		}
		polygonMesh->createFace(ids[0], ids[1], ids[2]);
	}
}
*/

PolygonMesh* PolygonMeshBuilder::getPolygonMesh()
{
	return polygonMesh;
}

void PolygonMeshBuilder::add(const int v0, const int v1, const int v2, const int v3)
{
	const auto& positions = polygonMesh->getPositions();
	const auto& p0 = positions[v0];
	const auto& p1 = positions[v1];
	const auto& p2 = positions[v2];

	const auto& normal = glm::cross(p1 - p0, p2 - p0);
	auto n0 = polygonMesh->createNormal(normal);

	auto vv0 = polygonMesh->createVertex(v0, n0);
	auto vv1 = polygonMesh->createVertex(v1, n0);
	auto vv2 = polygonMesh->createVertex(v2, n0);
	auto vv3 = polygonMesh->createVertex(v3, n0);

	polygonMesh->createFace( vv0, vv1, vv2 );
	polygonMesh->createFace( vv0, vv2, vv3) ;
}
