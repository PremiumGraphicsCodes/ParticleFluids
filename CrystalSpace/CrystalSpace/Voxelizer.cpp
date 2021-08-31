#include "Voxelizer.h"

#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "SpaceHash3d.h"
#include "Octree.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	vx_mesh_t* toMesh(const PolygonMesh& polygon)
	{
		const auto positions = polygon.getPositions();
		const auto vertices = polygon.getVertices();
		const auto faces = polygon.getFaces();

		std::vector<int> indices;
		for (const auto& f : faces) {
			indices.push_back(vertices[f.getV1()].positionId);
			indices.push_back(vertices[f.getV2()].positionId);
			indices.push_back(vertices[f.getV3()].positionId);
		}

		auto mesh = vx_mesh_alloc(positions.size(), indices.size());

		for (int i = 0; i < positions.size(); ++i) {
			mesh->vertices[i].x = positions[i].x;
			mesh->vertices[i].y = positions[i].y;
			mesh->vertices[i].z = positions[i].z;
		}
		for (int i = 0; i < indices.size(); ++i) {
			mesh->indices[i] = indices[i];
		}

		return mesh;
	}

	bool check_overlap(const Box3dd& box, const Triangle3d& triangle)
	{
		return box.hasIntersection(triangle.getBoundingBox());
	}
}

std::vector<Vector3dd> Voxelizer::voxelizeToPoints(const PolygonMesh& polygon, const float res)
{
	vx_point_cloud_t* result;

	auto mesh = toMesh(polygon);

	const float precision = 0.0;//0.01;

	// Run voxelization
	result = vx_voxelize_pc(mesh, res, res, res, precision);

	std::vector<Vector3dd> points;
	for (int i = 0; i < result->nvertices; ++i) {
		const auto v = result->vertices[i];
		Vector3df p( v.x, v.y, v.z);
		points.push_back(p);
	}

	vx_point_cloud_free(result);
	vx_mesh_free(mesh);
	return points;
}

std::vector<Vector3dd> Voxelizer::voxelizeToPoints(const PolygonMesh& polygon, const std::array<int, 3>& res)
{
	const auto bb = polygon.getBoundingBox();
	const auto length = bb.getLength();

	auto m = toMesh(polygon);

	const float resx = length.x / res[0];
	const float resy = length.y / res[1];
	const float resz = length.z / res[2];

	vx_point_cloud_t* pc = vx_voxelize_pc(m, resx, resy, resz, 0.0);

	std::vector<Vector3dd> points;
	for (int i = 0; i < pc->nvertices; ++i) {
		const auto v = pc->vertices[i];
		Vector3df p(v.x, v.y, v.z);
		points.push_back(p);
	}

	vx_mesh_free(m);
	return points;
}

std::unique_ptr<Voxel> Voxelizer::voxelize(const PolygonMesh& polygon, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto xres = static_cast<size_t>( bb.getLength().x / res);
	const auto yres = static_cast<size_t>( bb.getLength().y / res);
	const auto zres = static_cast<size_t>(bb.getLength().z / res);
	std::array<size_t, 3> ress = { xres, yres, zres };
	auto voxel = std::make_unique<Voxel>(bb, ress);

	SpaceHash3d table(res, 1000);
	const auto faces = polygon.getFaces();
	
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < 1.0e-12) {
			continue;
		}
		const auto bb = triangle.getBoundingBox();

		const auto voxelSize = Vector3dd(res);
		for (float x = bb.getMinX(); x <= bb.getMaxX(); x += voxelSize.x) {
			for (float y = bb.getMinY(); y <= bb.getMaxY(); y += voxelSize.y) {
				for (float z = bb.getMinZ(); z <= bb.getMaxZ(); z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;
					const auto v2 = p + voxelSize * 0.5;
					Box3dd smallBox(v1, v2);

					// HACK: some holes might appear, this
					// precision factor reduces the artifact
						//halfsize.x += precision;
						//halfsize.y += precision;
						//halfsize.z += precision;

					if (::check_overlap(smallBox, triangle)) {
						table.add(new Particle<bool>(p, false));
					}
				}
			}
		}

	}

	/*
	auto m = toMesh(polygon);

	const auto width = res[0];
	const auto height = res[1];
	const auto depth = res[2];
	auto grid = vx_voxelize(m, width, height, depth);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (int k = 0; k < depth; ++k) {
				auto index = i + i * width + i * (width * height);
				auto v = grid[index];
				voxel->setValue(i, j, k, v);
			}
		}
	}
	*/

	return voxel;
}
