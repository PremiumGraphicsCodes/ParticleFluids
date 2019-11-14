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

void PolygonMeshBuilder::addOpen(const ISurface3d& surface, const int unum, const int vnum)
{
	std::vector<std::vector<int>> grid2d;
	for (int i = 0; i <= unum; ++i) {
		const auto u = i / static_cast<double>(unum);
		std::vector<int> grid1d;
		for (int j = 0; j <= vnum; ++j) {
			const auto v = j / static_cast<double>(vnum);
			const auto p = polygonMesh->createPosition( surface.getPosition( u, v) );
			const auto n = polygonMesh->createNormal( surface.getNormal(u, v) );
			const auto tx = polygonMesh->createTexCoord(Vector2dd( u,v) );
			const auto id = polygonMesh->createVertex(p, n, tx);
			grid1d.push_back(id);
		}
		grid2d.push_back(grid1d);
	}
	for (int i = 0; i < grid2d.size()-1; ++i) {
		for (int j = 0; j < grid2d[i].size() - 1; ++j) {
			polygonMesh->createFace( grid2d[i][j], grid2d[i + 1][j], grid2d[i][j + 1] );
			polygonMesh->createFace( grid2d[i][j + 1], grid2d[i + 1][j], grid2d[i + 1][j + 1] );
		}
	}
}

void PolygonMeshBuilder::addClosed(const ISurface3d& surface, const int unum, const int vnum)
{
	std::vector<std::vector<int>> grid2d;
	for (int i = 0; i <= unum; ++i) {
		const auto u = i / static_cast<double>(unum);
		std::vector<int> grid1d;
		for (int j = 0; j <= vnum; ++j) {
			const auto v = j / static_cast<double>(vnum);
			const auto p = polygonMesh->createPosition(surface.getPosition(u, v));
			const auto n = polygonMesh->createNormal(surface.getNormal(u, v));
			const auto tx = polygonMesh->createTexCoord(Vector2dd(u, v));
			const auto id = polygonMesh->createVertex(p, n, tx);
			grid1d.push_back(id);
		}
		grid2d.push_back(grid1d);
	}
	for (int i = 0; i < grid2d.size()-1; ++i) {
		for (int j = 0; j < grid2d[i].size()-1; ++j) {
			const auto ii = (i + 1);// % grid2d.size();
			const auto jj = (j + 1);// % grid2d[i].size();
			polygonMesh->createFace(grid2d[i][j], grid2d[ii][j], grid2d[i][jj]);
			polygonMesh->createFace(grid2d[i][jj], grid2d[ii][j], grid2d[ii][jj]);
		}
	}
}

void PolygonMeshBuilder::add(const IVolume3d& volume, const int unum, const int vnum, const int wnum)
{
	auto p0 = polygonMesh->createPosition(volume.getPosition(0, 0, 0));
	auto p1 = polygonMesh->createPosition(volume.getPosition(1, 0, 0));
	auto p2 = polygonMesh->createPosition(volume.getPosition(1, 1, 0));
	auto p3 = polygonMesh->createPosition(volume.getPosition(0, 1, 0));

	auto p4 = polygonMesh->createPosition(volume.getPosition(0, 0, 1));
	auto p5 = polygonMesh->createPosition(volume.getPosition(1, 0, 1));
	auto p6 = polygonMesh->createPosition(volume.getPosition(1, 1, 1));
	auto p7 = polygonMesh->createPosition(volume.getPosition(0, 1, 1));

	add(p0, p1, p2, p3); // front
	add(p7, p6, p5, p4); // back
	add(p3, p2, p6, p7); // top
	add(p0, p1, p5, p4); // bottom
	add(p0, p4, p7, p3); // left
	add(p1, p5, p6, p2); // right
	/*
	std::vector<std::vector<std::vector<int>>> grid3d;
	for (int i = 0; i <= unum; ++i) {
		const auto u = i / static_cast<double>(unum);
		std::vector<std::vector<int>> grid2d;
		for (int j = 0; j <= vnum; ++j) {
			const auto v = j / static_cast<double>(vnum);
			std::vector<int> grid1d;
			for (int k = 0; k <= wnum; ++k) {
				const auto w = j / static_cast<double>(wnum);
				const auto p = polygonMesh->createPosition(volume.getPosition(u, v, w));
				grid1d.push_back(p);
			}
			grid2d.push_back(grid1d);
		}
		grid3d.push_back(grid2d);
	}
	*/
}

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
