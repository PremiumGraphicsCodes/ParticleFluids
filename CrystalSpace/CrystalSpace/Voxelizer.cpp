#include "Voxelizer.h"

#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"

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

	vx_aabb_t* calculateAABB(vx_mesh_t* m)
	{
		vx_aabb_t* meshaabb = NULL;

		for (size_t i = 0; i < m->nindices; i += 3) {
			vx_triangle_t triangle;
			unsigned int i1, i2, i3;

			VX_ASSERT(m->indices[i + 0] < m->nvertices);
			VX_ASSERT(m->indices[i + 1] < m->nvertices);
			VX_ASSERT(m->indices[i + 2] < m->nvertices);

			i1 = m->indices[i + 0];
			i2 = m->indices[i + 1];
			i3 = m->indices[i + 2];

			triangle.p1 = m->vertices[i1];
			triangle.p2 = m->vertices[i2];
			triangle.p3 = m->vertices[i3];

			if (!meshaabb) {
				meshaabb = VX_MALLOC(vx_aabb_t, 1);
				*meshaabb = vx__triangle_aabb(&triangle);
			}
			else {
				vx_aabb_t naabb = vx__triangle_aabb(&triangle);
				*meshaabb = vx__aabb_merge(meshaabb, &naabb);
			}
		}
		return meshaabb;
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

std::unique_ptr<Voxel> Voxelizer::voxelize(const PolygonMesh& polygon, const std::array<size_t, 3>& res)
{
	const auto bb = polygon.getBoundingBox();
	auto voxel = std::make_unique<Voxel>(bb, res);

	auto m = toMesh(polygon);

	const auto width = res[0];
	const auto height = res[1];
	const auto depth = res[2];
	auto grid = vx_voxelize_snap_3dgrid(m, width, height, depth);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (int k = 0; k < depth; ++k) {
				auto index = i + i * width + i * (width * height);
				auto v = grid[index];
				voxel->setValue(i, j, k, v);
			}
		}
	}

	VX_FREE(grid);
	return voxel;
}
