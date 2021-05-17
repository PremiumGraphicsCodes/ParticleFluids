#include "MeshToVoxelConverter.h"

#include "../../Crystal/Math/Triangle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void MeshToVoxelConverter::convert(const PolygonMesh& mesh, const double divideLength)
{
	const auto box = mesh.getBoundingBox();

	const auto resx = static_cast<int>( box.getLength().x / divideLength );
	const auto resy = static_cast<int>( box.getLength().y / divideLength );
	const auto resz = static_cast<int>( box.getLength().z / divideLength );
	voxel.setBox(box);
	voxel.setResolution({ resx, resy, resz });

	const auto& positions = mesh.getPositions();
	const auto& faces = mesh.getFaces();
	for (const auto& f : faces) {
		const auto& triangle = f.toTriangle(positions);
		subdivide(triangle, divideLength);
	}
}

void MeshToVoxelConverter::subdivide(const Triangle3d& triangle, const double divideLength)
{
	const auto& vertices = triangle.getVertices();
	const auto box = triangle.getBoundingBox();
	const auto distanceSquared = getDistanceSquared(box.getMin(), box.getMax());
	if (distanceSquared < divideLength * divideLength) {
		positions.push_back(box.getCenter());
		return;
	}
	const auto& v0 = vertices[0];
	const auto& v1 = vertices[1];
	const auto& v2 = vertices[2];

	const Line3dd e01(v0, v1 - v0);
	const Line3dd e12(v1, v2 - v1);
	const Line3dd e20(v2, v0 - v2);
	const auto& v01 = e01.getPosition(0.5);
	const auto& v12 = e12.getPosition(0.5);
	const auto& v20 = e20.getPosition(0.5);

	subdivide(Triangle3d(v0, v01, v20), divideLength);
	subdivide(Triangle3d(v01, v1, v12), divideLength);
	subdivide(Triangle3d(v20, v12, v2), divideLength);
	subdivide(Triangle3d(v01, v12, v20), divideLength);
}

void MeshToVoxelConverter::toVoxel(const double divideLength)
{
	const auto origin = voxel.getBoundingBox().getMin();
	for (const auto& p : positions) {
		const auto localPos = p - origin;
		const auto ix = static_cast<int>( localPos.x / divideLength );
		const auto iy = static_cast<int>( localPos.y / divideLength );
		const auto iz = static_cast<int>( localPos.z / divideLength );
		const std::array<int,3> index = { ix, iy, iz };
		const bool exits = voxel.exists(index);
		if (!exits) {
			auto node = voxel.createNode(index);
			node->setValue(true);
		}
	}
}
