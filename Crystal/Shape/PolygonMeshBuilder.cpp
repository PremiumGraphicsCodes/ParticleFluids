#include "PolygonMeshBuilder.h"

#include "TriangleMesh.h"

#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Plane3d.h"
#include "../Math/Quad3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMeshBuilder::PolygonMeshBuilder() :
	polygonMesh(new PolygonMesh()),
	nextFaceId(0)
{}

void PolygonMeshBuilder::add(const Triangle3d& triangle)
{
	auto vertexFactory = polygonMesh->getVertexFactory();
	const auto& vs = triangle.getVertices();
	auto normal = vertexFactory->createNormal( triangle.getNormal() );
	auto p0 = vertexFactory->createPosition(vs[0]);
	auto p1 = vertexFactory->createPosition(vs[1]);
	auto p2 = vertexFactory->createPosition(vs[2]);
	auto v0 = vertexFactory->createVertex( p0, normal)->getId();
	auto v1 = vertexFactory->createVertex( p1, normal)->getId();
	auto v2 = vertexFactory->createVertex( p2, normal)->getId();
	auto f = Face(v0, v1, v2, nextFaceId++);
	FaceGroup group;
	group.faces.push_back(f);
	polygonMesh->addFaceGroup(group);
}

void PolygonMeshBuilder::add(const Box3d& box)
{
	auto vertexFactory = polygonMesh->getVertexFactory();
	auto p0 = vertexFactory->createPosition(box.getPosition(Vector3dd(0, 0, 0)));
	auto p1 = vertexFactory->createPosition(box.getPosition(Vector3dd(1, 0, 0)));
	auto p2 = vertexFactory->createPosition(box.getPosition(Vector3dd(1, 1, 0)));
	auto p3 = vertexFactory->createPosition(box.getPosition(Vector3dd(0, 1, 0)));

	auto p4 = vertexFactory->createPosition(box.getPosition(Vector3dd(0, 0, 1)));
	auto p5 = vertexFactory->createPosition(box.getPosition(Vector3dd(1, 0, 1)));
	auto p6 = vertexFactory->createPosition(box.getPosition(Vector3dd(1, 1, 1)));
	auto p7 = vertexFactory->createPosition(box.getPosition(Vector3dd(0, 1, 1)));

	FaceGroup group;
	add(p0, p1, p2, p3, group); // front
	add(p7, p6, p5, p4, group); // back
	add(p3, p2, p6, p7, group); // top
	add(p0, p1, p5, p4, group); // bottom
	add(p0, p4, p7, p3, group); // left
	add(p1, p5, p6, p2, group); // right;
	polygonMesh->addFaceGroup(group);
}

void PolygonMeshBuilder::add(const Sphere3d& sphere, const int unum, const int vnum)
{
	auto vertexFactory = polygonMesh->getVertexFactory();

	const auto du = 1.0 / (double)unum;
	const auto dv = 1.0 / (double)vnum;
	std::vector<std::vector<int>> grid;
	for (double u = 0.0; u < 1.0; u +=du) {
		std::vector<int> vs;
		for (double v = 0.0; v < 1.0; v+=dv) {
			auto p = vertexFactory->createPosition( sphere.getPosition(Vector3dd( u, v, 1.0)) );
			auto n = vertexFactory->createNormal( sphere.getNormal(u, v) );
			auto tx = vertexFactory->createTexCoord(Vector2dd( u,v) );
			const auto id = vertexFactory->createVertex(p, n, tx)->getId();
			vs.push_back(id);
		}
		grid.push_back(vs);
	}
	FaceGroup faceGroup;
	for (int i = 0; i < grid.size()-1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			faceGroup.faces.push_back( Face( grid[i][j], grid[i + 1][j], grid[i][j + 1] ) );
			faceGroup.faces.push_back( Face(grid[i][j + 1], grid[i + 1][j], grid[i + 1][j + 1] ) );
		}
	}
	polygonMesh->addFaceGroup(faceGroup);
}

void PolygonMeshBuilder::add(const Quad3d& quad)
{
	auto vertexFactory = polygonMesh->getVertexFactory();

	auto normal = vertexFactory->createNormal( quad.getNormal() );

	auto v0 = vertexFactory->createVertex( vertexFactory->createPosition( quad.getPosition(0, 0) ), normal, vertexFactory->createTexCoord( Vector2dd(0, 0)) )->getId();
	auto v1 = vertexFactory->createVertex( vertexFactory->createPosition( quad.getPosition(1, 0) ), normal, vertexFactory->createTexCoord( Vector2dd(1, 0)) )->getId();
	auto v2 = vertexFactory->createVertex( vertexFactory->createPosition( quad.getPosition(1, 1) ), normal, vertexFactory->createTexCoord( Vector2dd(1, 1)) )->getId();
	auto v3 = vertexFactory->createVertex( vertexFactory->createPosition( quad.getPosition(0, 1) ), normal, vertexFactory->createTexCoord( Vector2dd(0, 1)) )->getId();

	FaceGroup faceGroup;
	faceGroup.faces.push_back(Face(v0, v1, v2));
	faceGroup.faces.push_back(Face(v3,v1,v2 ));
	polygonMesh->addFaceGroup(faceGroup);
}

void PolygonMeshBuilder::add(const TriangleMesh& mesh)
{
	auto vertexFactory = polygonMesh->getVertexFactory();
	const auto& fs = mesh.getFaces();
	FaceGroup faceGroup;
	for (const auto& f : fs) {
		const auto& vs = f.getVertices();
		const auto& normal = f.getNormal();
		auto n = vertexFactory->createNormal(normal);
		std::array<int,3> ids;
		for (int i = 0; i < 3; ++i ) {
			auto p = vertexFactory->createPosition(vs[i]);
			ids[i] = vertexFactory->createVertex(p, n)->getId();
		}
		faceGroup.faces.push_back( Face(ids[0], ids[1], ids[2]) );
	}
	polygonMesh->addFaceGroup(faceGroup);
}

PolygonMesh* PolygonMeshBuilder::getPolygonMesh()
{
	return polygonMesh;
}

void PolygonMeshBuilder::add(Vector3dd* p0, Vector3dd* p1, Vector3dd* p2, Vector3dd* p3, FaceGroup& faceGroup)
{
	auto vertexFactory = polygonMesh->getVertexFactory();

	const auto& normal = glm::cross(*p1 - *p0, *p2 - *p0);
	auto n0 = vertexFactory->createNormal(normal);

	auto v0 = vertexFactory->createVertex(p0, n0)->getId();
	auto v1 = vertexFactory->createVertex(p1, n0)->getId();
	auto v2 = vertexFactory->createVertex(p2, n0)->getId();
	auto v3 = vertexFactory->createVertex(p3, n0)->getId();

	faceGroup.faces.push_back( Face( v0,v1,v2 ));
	faceGroup.faces.push_back(Face(v0, v2, v3));
}
