#include "MeshToParticleAlgo.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Circle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

void MeshToParticleAlgo::subdivide(const PolygonMesh& mesh, const double divideLength)
{
	const auto& positions = mesh.getPositions();
	const auto& faces = mesh.getFaces();
	for (auto f : faces) {
		const auto& triangle = f.toTriangle(positions);
		subdivide(triangle, divideLength);
	}
}

void MeshToParticleAlgo::subdivide(const Triangle3d& triangle, const double divideLength)
{
	const auto& vertices = triangle.getVertices();
	const auto box = triangle.getBoundingBox();
	const auto distanceSquared = getDistanceSquared(box.getMin(), box.getMax());
	if (distanceSquared < divideLength * divideLength) {
		positions.push_back(box.getCenter());
		normals.push_back(triangle.getNormal());
		return;
	}
	const auto v0 = vertices[0];
	const auto v1 = vertices[1];
	const auto v2 = vertices[2];

	const Line3dd e01(v0, v1-v0);
	const Line3dd e12(v1, v2-v1);
	const Line3dd e20(v2, v0-v2);
	const auto& v01 = e01.getPosition(0.5);
	const auto& v12 = e12.getPosition(0.5);
	const auto& v20 = e20.getPosition(0.5);

	subdivide(Triangle3d(v0, v01, v20), divideLength);
	subdivide(Triangle3d(v01, v1, v12), divideLength);
	subdivide(Triangle3d(v20, v12, v2), divideLength);
	subdivide(Triangle3d(v01, v12, v20), divideLength);
}