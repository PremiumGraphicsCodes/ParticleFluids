#include "VDBPolygonMeshConverter.h"

#include "VDBPolygonMeshScene.h"
#include "VDBPolygonMeshImpl.h"
#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include <openvdb/tools/MeshToVolume.h>

using namespace Crystal::Math;
using namespace Crystal::VDB;

void VDBPolygonMeshConverter::toVolume(const VDBPolygonMeshScene& mesh, VDBVolumeScene* volume, const double divideLength)
{
	openvdb::math::Transform::Ptr xform = openvdb::math::Transform::createLinearTransform();
	const auto quads = mesh.getImpl()->getQuads();
	std::vector<openvdb::Vec3s> points = mesh.getImpl()->points;
	for (auto& p : points) {
		p *= divideLength;
	}
	openvdb::tools::QuadAndTriangleDataAdapter<openvdb::Vec3s, openvdb::Vec4I> m(mesh.getImpl()->points, quads);
	auto result = openvdb::tools::meshToVolume<openvdb::FloatGrid>(m, *xform);
	auto impl = new VDBVolumeImpl(result);
	impl->setScale(1.0 / divideLength);
	delete volume->getImpl();
	volume->setImpl(impl);
}

void VDBPolygonMeshConverter::fromVDB(const VDBPolygonMeshScene& src, Crystal::Shape::PolygonMesh* mesh)
{
	auto vertices = src.getVerticesd();

	auto triangles = src.getTriangleFaces();
	auto quads = src.getQuadFaces();

	Crystal::Shape::PolygonMeshBuilder builder;

	for (const auto& v : vertices) {
		int id = builder.createPosition(v);
		//		builder.createVertex(id, normalId);
	}

	for (const auto& tt : triangles) {
		const auto t = tt.indices;
		builder.createFace(t[0], t[1], t[2]);
	}

	for (const auto& tt : quads) {
		const auto t = tt.indices;
		{
			const auto normal = tt.normal;
			const auto normalId = builder.createNormal(normal);
			const auto v00 = builder.createVertex(t[0], normalId);
			const auto v01 = builder.createVertex(t[1], normalId);
			const auto v02 = builder.createVertex(t[2], normalId);
			builder.createFace(v00, v01, v02);
		}
		{
			const auto normal = tt.normal;
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
}
