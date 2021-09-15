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

void ScanLineVoxelizer::voxelize(const PolygonMesh& polygon, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto min = bb.getMin() - Vector3dd(e, e, e);
	const auto max = bb.getMax() + Vector3dd(e, e, e);

	const Box3dd space(min, max);
	RayTracer rayTracer;
	rayTracer.build(space, 4);
	const auto positions = polygon.getPositions();
	const auto& faces = polygon.getFaces();
	for (const auto& f : faces) {
		RayTraceItem* item = new RayTraceItem(f.toTriangle(positions));
		rayTracer.add(item);
	}
	for (auto y = min.y; y < max.y; y += res) {
		for (auto z = min.z; z < min.z; z += res) {
			const Ray3d ray(Vector3dd(min.x, y, z), Vector3dd(1, 0, 0));
//			rayTracer.
		}
	}
	rayTracer.clear();
	//rayTracer.c
	//rayTracer.trace()
}
