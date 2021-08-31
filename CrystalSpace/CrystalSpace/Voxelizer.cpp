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

	SpaceHash3d table(1.0, 1000);
	const auto faces = polygon.getFaces();
	
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < 1.0e-12) {
			continue;
		}
		const auto bb = triangle.getBoundingBox();

		//Octree octree;
		//octree.add()
		//for(auto x = bb.getMinX(); x < bb.getMaxX(); x+= dx)
	}

		/*
			if (vx__triangle_area(&triangle) < VOXELIZER_EPSILON) {
				// triangle with 0 area
				continue;
			}

			vx_aabb_t aabb = vx__triangle_aabb(&triangle);

			aabb.min.x = vx__map_to_voxel(aabb.min.x, vs.x, true);
			aabb.min.y = vx__map_to_voxel(aabb.min.y, vs.y, true);
			aabb.min.z = vx__map_to_voxel(aabb.min.z, vs.z, true);

			aabb.max.x = vx__map_to_voxel(aabb.max.x, vs.x, false);
			aabb.max.y = vx__map_to_voxel(aabb.max.y, vs.y, false);
			aabb.max.z = vx__map_to_voxel(aabb.max.z, vs.z, false);

			for (float x = aabb.min.x; x <= aabb.max.x; x += vs.x) {
				for (float y = aabb.min.y; y <= aabb.max.y; y += vs.y) {
					for (float z = aabb.min.z; z <= aabb.max.z; z += vs.z) {
						vx_aabb_t saabb;

						saabb.min.x = x - hvs.x;
						saabb.min.y = y - hvs.y;
						saabb.min.z = z - hvs.z;
						saabb.max.x = x + hvs.x;
						saabb.max.y = y + hvs.y;
						saabb.max.z = z + hvs.z;

						vx_vertex_t boxcenter = vx__aabb_center(&saabb);
						vx_vertex_t halfsize = vx__aabb_half_size(&saabb);

						// HACK: some holes might appear, this
						// precision factor reduces the artifact
						halfsize.x += precision;
						halfsize.y += precision;
						halfsize.z += precision;

						if (vx__triangle_box_overlap(boxcenter, halfsize, triangle)) {
							vx_vec3_t v1, v2, v3;
							vx_color_t c1, c2, c3;
							vx_voxel_data_t* nodedata;
							float a1, a2, a3;
							float area;

							nodedata = VX_MALLOC(vx_voxel_data_t, 1);

							if (m->colors != NULL) {
								// Perform barycentric interpolation of colors
								v1 = triangle.p1;
								v2 = triangle.p2;
								v3 = triangle.p3;

								c1 = triangle.colors[0];
								c2 = triangle.colors[1];
								c3 = triangle.colors[2];

								vx_triangle_t t1 = { {{v1, v2, boxcenter}}, {{{{0.0f, 0.0f, 0.0f}}}} };
								vx_triangle_t t2 = { {{v2, v3, boxcenter}}, {{{{0.0f, 0.0f, 0.0f}}}} };
								vx_triangle_t t3 = { {{v3, v1, boxcenter}}, {{{{0.0f, 0.0f, 0.0f}}}} };

								a1 = vx__triangle_area(&t1);
								a2 = vx__triangle_area(&t2);
								a3 = vx__triangle_area(&t3);

								area = a1 + a2 + a3;

								vx__vec3_multiply(&c1, a2 / area);
								vx__vec3_multiply(&c2, a3 / area);
								vx__vec3_multiply(&c3, a1 / area);

								vx__vec3_add(&c1, &c2);
								vx__vec3_add(&c1, &c3);

								nodedata->color = c1;
							}

							nodedata->position = boxcenter;

							size_t hash = vx__vertex_hash(boxcenter, VOXELIZER_HASH_TABLE_SIZE);

							bool insert = vx__hash_table_insert(table, hash, nodedata,
								vx__vertex_comp_func);

							if (insert) {
								(*nvoxels)++;
							}
						}
					}
				}
			}
		}

		return table;
	}
	*/

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
