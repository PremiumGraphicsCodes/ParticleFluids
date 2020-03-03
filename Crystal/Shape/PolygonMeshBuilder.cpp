#include "PolygonMeshBuilder.h"

#include "../Math/Triangle3d.h"
#include "../Math/Line3d.h"
#include "../Math/Sphere3d.h"
#include "../Math/Plane3d.h"
#include "../Math/Quad3d.h"
#include "../Math/Box3d.h"
#include "../Math/Cone3d.h"

#include "CircularBuffer.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

PolygonMeshBuilder::PolygonMeshBuilder() :
	nextVertexId(0),
	nextFaceId(0)
{}

void PolygonMeshBuilder::add(const Triangle3d& triangle)
{
	const auto& vs = triangle.getVertices();
	const auto p0 = createPosition(vs[0]);
	const auto p1 = createPosition(vs[1]);
	const auto p2 = createPosition(vs[2]);
	const auto n = createNormal(triangle.getNormal());
	const auto v0 = createVertex(p0, n, -1);
	const auto v1 = createVertex(p1, n, -1);
	const auto v2 = createVertex(p2, n, -1);
	createFace(v0, v1, v2);
}

void PolygonMeshBuilder::add(const Quad3d& quad)
{
	const auto p0 = createPosition(quad.getPosition(0.0, 0.0));
	const auto p1 = createPosition(quad.getPosition(1.0, 0.0));
	const auto p2 = createPosition(quad.getPosition(0.0, 1.0));
	const auto p3 = createPosition(quad.getPosition(1.0, 1.0));
	const auto n = createNormal(quad.getNormal());
	const auto t0 = createTexCoord(Vector2dd(0.0, 0.0));
	const auto t1 = createTexCoord(Vector2dd(1.0, 0.0));
	const auto t2 = createTexCoord(Vector2dd(0.0, 1.0));
	const auto t3 = createTexCoord(Vector2dd(1.0, 1.0));
	const auto v0 = createVertex(p0, n, t0);
	const auto v1 = createVertex(p1, n, t1);
	const auto v2 = createVertex(p2, n, t2);
	const auto v3 = createVertex(p3, n, t3);
	createFace(v0, v1, v2);
	createFace(v3, v2, v1);
}

void PolygonMeshBuilder::add(const Box3d& box)
{
	auto p0 = createPosition(box.getPosition(0, 0, 0));
	auto p1 = createPosition(box.getPosition(1, 0, 0));
	auto p2 = createPosition(box.getPosition(1, 1, 0));
	auto p3 = createPosition(box.getPosition(0, 1, 0));

	auto p4 = createPosition(box.getPosition(0, 0, 1));
	auto p5 = createPosition(box.getPosition(1, 0, 1));
	auto p6 = createPosition(box.getPosition(1, 1, 1));
	auto p7 = createPosition(box.getPosition(0, 1, 1));

	auto n0 = createNormal(Vector3dd( 1, 0, 0));
	auto n1 = createNormal(Vector3dd(-1, 0, 0));
	auto n2 = createNormal(Vector3dd( 0, 1, 0));
	auto n3 = createNormal(Vector3dd( 0,-1, 0));
	auto n4 = createNormal(Vector3dd( 0, 0, 1));
	auto n5 = createNormal(Vector3dd( 0, 0,-1));

	/*
	auto t0 = createTexCoord(Vector2dd(0, 0));
	auto t1 = createTexCoord(Vector2dd(1, 0));
	auto t2 = createTexCoord(Vector2dd(1, 1));
	auto t3 = createTexCoord(Vector2dd(0, 1));

	auto t4 = createTexCoord(Vector2dd(0, 0));
	auto t5 = createTexCoord(Vector2dd(1, 0));
	auto t6 = createTexCoord(Vector2dd(1, 1));
	auto t7 = createTexCoord(Vector2dd(0, 1));

	auto t8 = createTexCoord(Vector2dd(0, 0));
	auto t9 = createTexCoord(Vector2dd(1, 0));
	auto t10 = createTexCoord(Vector2dd(1, 1));
	auto t11 = createTexCoord(Vector2dd(0, 1));

	auto t12 = createTexCoord(Vector2dd(0, 0));
	auto t13 = createTexCoord(Vector2dd(1, 0));
	auto t14 = createTexCoord(Vector2dd(1, 1));
	auto t15 = createTexCoord(Vector2dd(0, 1));
	*/

	auto v0 = createVertex(p0, n5);
	auto v1 = createVertex(p1, n5);
	auto v2 = createVertex(p2, n5);
	auto v3 = createVertex(p3, n5);
	auto v4 = createVertex(p4, n4);
	auto v5 = createVertex(p5, n4);
	auto v6 = createVertex(p5, n4);
	auto v7 = createVertex(p5, n4);

	createFace(v0, v1, v2); // front
	createFace(v3, v2, v1);
	createFace(v4, v5, v6);
	createFace(v7, v4, v5);

	/*
	add(p0, p1, p2, p3); // front
	add(p7, p6, p5, p4); // back
	add(p3, p2, p6, p7); // top
	add(p0, p1, p5, p4); // bottom
	add(p0, p4, p7, p3); // left
	add(p1, p5, p6, p2); // right
	*/
}

void PolygonMeshBuilder::add(const Sphere3d& sphere, const int unum, const int vnum)
{
	std::vector<std::vector<int>> positions(unum);
	std::vector<std::vector<int>> normals(unum);
	std::vector<std::vector<int>> texCoords(unum);

	for (int i = 0; i < unum; ++i) {
		positions[i].resize(vnum);
		normals[i].resize(vnum);
		texCoords[i].resize(vnum);

		const auto u = i / (double)(unum-1);
		for (int j = 0; j < vnum; ++j) {
			const auto v = j / (double)(vnum-1);
			positions[i][j] = createPosition(sphere.getPosition( u, v ));
			normals[i][j] = createNormal(sphere.getNormal(u, v));
			texCoords[i][j] = createTexCoord(Vector2dd(u, v));
		}
	}

	CircularBuffer<CircularBuffer<int>> vertices(unum);
	for (int i = 0; i < unum; ++i) {
		vertices[i].resize(vnum);
		for (int j = 0; j < vnum; ++j) {
			vertices[i][j] = createVertex(positions[i][j], normals[i][j], texCoords[i][j]);
		}
	}
	for (int i = 0; i < unum; ++i) {
		for (int j = 0; j < vnum; ++j) {
			createFace(vertices[i][j], vertices[i+1][j], vertices[i][j+1]);
			createFace(vertices[i+1][j+1], vertices[i][j+1], vertices[i+1][j]);
		}
	}
}

void PolygonMeshBuilder::add(const Cone3d& cone, int unum)
{
	assert(false);
}


std::unique_ptr<PolygonMesh> PolygonMeshBuilder::build()
{
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = positions;
	mesh->normals = normals;
	mesh->texCoords = texCoords;
	mesh->vertices = vertices;
	mesh->faces = faces;
	return std::move(mesh);
}

void PolygonMeshBuilder::add(const int v0, const int v1, const int v2, const int v3)
{
	const auto& p0 = positions[v0];
	const auto& p1 = positions[v1];
	const auto& p2 = positions[v2];

	const auto& normal = glm::cross(p1 - p0, p2 - p0);
	auto n0 = createNormal(normal);

	auto vv0 = createVertex(v0, n0);
	auto vv1 = createVertex(v1, n0);
	auto vv2 = createVertex(v2, n0);
	auto vv3 = createVertex(v3, n0);

	createFace(vv0, vv1, vv2);
	createFace(vv0, vv2, vv3);
}

Vector3dd PolygonMeshBuilder::calculateNormal(const int v0, const int v1, const int v2)
{
	const auto& p0 = positions[v0];
	const auto& p1 = positions[v1];
	const auto& p2 = positions[v2];

	return glm::normalize( glm::cross(p1 - p0, p2 - p0) );
}

int PolygonMeshBuilder::createPosition(const Vector3dd& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

int PolygonMeshBuilder::createNormal(const Vector3dd& v)
{
	normals.push_back(v);
	return static_cast<int>(normals.size() - 1);
}

int PolygonMeshBuilder::createTexCoord(const Vector2dd& v)
{
	texCoords.push_back(v);
	return static_cast<int>(texCoords.size() - 1);
}

int PolygonMeshBuilder::createVertex(const int positionId, const int normalId, const int texCoordId)
{
	Vertex v;
	v.positionId = positionId;
	v.normalId = normalId;
	v.texCoordId = texCoordId;
	v.id = nextVertexId++;
	vertices.push_back(v);
	return v.id;
}

int PolygonMeshBuilder::createFace(int v0, int v1, int v2)
{
	Face f(v0, v1, v2, nextFaceId++);
	faces.push_back(f);
	return f.getId();
}
