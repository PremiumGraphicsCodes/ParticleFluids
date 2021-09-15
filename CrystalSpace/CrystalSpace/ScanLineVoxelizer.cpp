#include "ScanLineVoxelizer.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "SpaceHash3d.h"
#include "Overlap.h"
#include "RayTracer.h"

using namespace Crystal::Util;
using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	const auto e = 1.0e-12;
}

void ScanLineVoxelizer::voxelize(const PolygonMesh& polygon, const Box3dd& space, const double res)
{
	RayTracer rayTracer;
	rayTracer.build(space, 4);
	const auto positions = polygon.getPositions();
	const auto& faces = polygon.getFaces();
	for (const auto& f : faces) {
		RayTraceItem* item = new RayTraceItem(f.toTriangle(positions));
		rayTracer.add(item);
	}

	//const Ray3d ray(Vector3dd(0.1, 5, 5), Vector3dd(1, 0, 0));
	//rayTracer.trace(ray, res);

	std::vector<Vector3dd> intersections;
	for (auto y = space.getMinY(); y < space.getMaxY(); y += res) {
		for (auto z = space.getMinZ(); z < space.getMaxZ(); z += res) {
			const Ray3d ray(Vector3dd(space.getMinX() + e, y + e, z + e), Vector3dd(1, 0, 0));
			rayTracer.trace(ray, res);
			auto is = rayTracer.getIntersections();
			for (const auto& i : is) {
				intersections.push_back(i);
			}
		}
	}
	rayTracer.clear();
	//rayTracer.c
	//rayTracer.trace()
}
