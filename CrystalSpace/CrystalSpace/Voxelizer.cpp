#include "Voxelizer.h"

#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void Voxelizer::voxelize(const PolygonMesh& polygon, const float res)
{
	vx_mesh_t* mesh;
	vx_point_cloud_t* result;

	const auto positions = polygon.getPositions();
	const auto vertices = polygon.getVertices();
	const auto faces = polygon.getFaces();

	std::vector<int> indices;
	for (const auto& f : faces) {
		indices.push_back( vertices[f.getV1()].positionId );
		indices.push_back( vertices[f.getV2()].positionId );
		indices.push_back( vertices[f.getV3()].positionId );
	}

	mesh = vx_mesh_alloc(positions.size(), indices.size() );

	for (int i = 0; i < positions.size(); ++i) {
		mesh->vertices[i].x = positions[i].x;
		mesh->vertices[i].y = positions[i].y;
		mesh->vertices[i].z = positions[i].z;
	}
	for (int i = 0; i < indices.size(); ++i) {
		mesh->indices[i] = indices[i];
	}

	// Precision factor to reduce "holes" artifact
//	const float res = 0.025;
//	const float res = 0.25;
	const float precision = 0.01;

	// Run voxelization
	result = vx_voxelize_pc(mesh, res, res, res, precision);

	for (int i = 0; i < result->nvertices; ++i) {
		const auto v = result->vertices[i];
		Vector3df p( v.x, v.y, v.z);
		this->points.push_back(p);
	}

	/*
	const auto width = 10;
	const auto height = 10;
	const auto depth = 10;
	auto result_volume = vx_voxelize_snap_3dgrid(mesh, width, height, depth);
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (int k = 0; k < depth; ++k) {
				auto index = i + i * width + i * (width * height);
				auto v = result_volume[index];
			}
		}
	}
	//result_volume.[0][0][0];
	*/

	vx_point_cloud_free(result);
	vx_mesh_free(mesh);
}