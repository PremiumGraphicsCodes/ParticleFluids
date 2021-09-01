#include "Voxelizer.h"

#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "SpaceHash3d.h"
#include "Overlap.h"

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
	const auto zres = static_cast<size_t>( bb.getLength().z / res);
	std::array<size_t, 3> ress = { xres, yres, zres };

	SpaceHash3d table(res, 1000);
	const auto faces = polygon.getFaces();

	const auto voxelSize = Vector3dd(res);
	
	std::vector<IParticle*> particles;
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < 1.0e-12) {
			continue;
		}
		const auto smallBB = triangle.getBoundingBox();

		for (float x = smallBB.getMinX(); x <= smallBB.getMaxX(); x += voxelSize.x) {
			for (float y = smallBB.getMinY(); y <= smallBB.getMaxY(); y += voxelSize.y) {
				for (float z = smallBB.getMinZ(); z <= smallBB.getMaxZ(); z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;
					const auto v2 = p + voxelSize * 0.5;
					Box3dd smallBox(v1, v2);

					// HACK: some holes might appear, this
					// precision factor reduces the artifact
						//halfsize.x += precision;
						//halfsize.y += precision;
						//halfsize.z += precision;
					Overlap o;
					if (o.overlap(smallBox, triangle)) {
						auto particle = new Particle<bool>(p, false);
						particles.push_back(particle);
						table.add(particle);
					}
				}
			}
		}
	}
	auto voxel = std::make_unique<Voxel>(bb, ress);
	voxel->fill(false);
	for (int i = 0; i < xres; ++i){
		const auto x = bb.getMinX() + i * voxelSize.x;
		for (int j = 0; j < yres; ++j) {
			const auto y = bb.getMinY() + j * voxelSize.y;
			for (int k = 0; k < zres; ++k) {
				const auto z = bb.getMinZ() + k * voxelSize.z;
				const Vector3dd p(x, y, z);
				if (!table.isEmpty(p)) {
					voxel->setValue(i, j, k, true);
				}
			}
		}
	}
	for (auto p : particles) {
		delete p;
	}
	return voxel;
}
