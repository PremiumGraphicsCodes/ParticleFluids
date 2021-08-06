#define VOXELIZER_IMPLEMENTATION

#include "../ThirdParty/voxelizer/voxelizer.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Shape;

void convert(PolygonMesh* polygon)
{
	vx_mesh_t* mesh;
	vx_mesh_t* result;

	const auto positions = polygon->getPositions();
	const auto vertices = polygon->getVertices();
	const auto faces = polygon->getFaces();

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
	const float res = 0.025;
	const float precision = 0.01;

	// Run voxelization
	result = vx_voxelize(mesh, res, res, res, precision);

	vx_mesh_free(result);
	vx_mesh_free(mesh);
}