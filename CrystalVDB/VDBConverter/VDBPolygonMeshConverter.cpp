#include "VDBPolygonMeshConverter.h"

#include "PolygonMeshImpl.h"
#include "VolumeImpl.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include <openvdb/tools/MeshToVolume.h>

using namespace Crystal::Math;
using namespace Crystal::VDB;

std::unique_ptr<VDBVolume> VDBPolygonMeshConverter::toVolume(const VDBPolygonMesh& mesh)
{
	openvdb::math::Transform::Ptr xform = openvdb::math::Transform::createLinearTransform();
	openvdb::tools::QuadAndTriangleDataAdapter<openvdb::Vec3s, openvdb::Vec4I> m(mesh.getImpl()->points, mesh.getImpl()->quads);
	auto result = openvdb::tools::meshToVolume<openvdb::FloatGrid>(m, *xform);
	auto impl = new VolumeImpl(result);
	return std::make_unique<VDBVolume>(impl);
}

namespace {
	Vector3dd getNormal(const std::vector<Vector3dd>& positions, const int p0, const int p1, const int p2)
	{
		const auto& v0 = positions[p0];
		const auto& v1 = positions[p1];
		const auto& v2 = positions[p2];
		const auto normal = glm::cross(glm::normalize(v2 - v1), glm::normalize(v0 - v1));
		return normal;
	}
}

std::unique_ptr<Crystal::Shape::PolygonMesh> VDBPolygonMeshConverter::fromVDB(const VDBPolygonMesh& src)
{
	auto mesh = std::make_unique<Crystal::Shape::PolygonMesh>();

	auto vertices = src.getVerticesd();

	auto triangles = src.getTriangles();
	auto quads = src.getQuads();

	Crystal::Shape::PolygonMeshBuilder builder;

	for (const auto& v : vertices) {
		int id = builder.createPosition(v);
		//		builder.createVertex(id, normalId);
	}

	for (const auto& t : triangles) {
		builder.createFace(t[0], t[1], t[2]);
	}

	for (const auto& t : quads) {
		{
			const auto normal = ::getNormal(vertices, t[0], t[1], t[2]);
			const auto normalId = builder.createNormal(normal);
			const auto v00 = builder.createVertex(t[0], normalId);
			const auto v01 = builder.createVertex(t[1], normalId);
			const auto v02 = builder.createVertex(t[2], normalId);
			builder.createFace(v00, v01, v02);
		}
		{
			const auto normal = ::getNormal(vertices, t[2], t[3], t[0]);
			const auto normalId = builder.createNormal(normal);
			const auto v00 = builder.createVertex(t[2], normalId);
			const auto v01 = builder.createVertex(t[3], normalId);
			const auto v02 = builder.createVertex(t[0], normalId);
			builder.createFace(v00, v01, v02);
		}
	}

	mesh->positions = builder.getPositions();
	mesh->normals = builder.getNormals();
	mesh->vertices = builder.getVertices();
	mesh->faces = builder.getFaces();

	return std::move(mesh);

	//return Crystal::Shape::PolygonMesh();
}
