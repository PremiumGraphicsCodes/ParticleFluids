#include "ScanLineVoxelizer.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Math/Ray3d.h"
#include "SpaceHash3d.h"
#include "Overlap.h"
#include "IntersectionCalculator.h"

using namespace Crystal::Util;
using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	const auto e = 1.0e-12;
}

void ScanLineVoxelizer::voxelize(const PolygonMesh& polygon, const Box3dd& space, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto xres = static_cast<size_t>(bb.getLength().x / res) + 1;
	const auto yres = static_cast<size_t>(bb.getLength().y / res) + 1;
	const auto zres = static_cast<size_t>(bb.getLength().z / res) + 1;
	std::array<size_t, 3> ress = { xres, yres, zres };

	const auto faces = polygon.getFaces();
	SpaceHash3d table(res, faces.size() * 3);

	const auto voxelSize = Vector3dd(res);

	std::vector<Particle<Triangle3d>*> particles;
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < e) {
			continue;
		}
		const auto smallBB = triangle.getBoundingBox();

		for (auto x = smallBB.getMinX(); x < smallBB.getMaxX() + e; x += voxelSize.x) {
			for (auto y = smallBB.getMinY(); y < smallBB.getMaxY() + e; y += voxelSize.y) {
				for (auto z = smallBB.getMinZ(); z < smallBB.getMaxZ() + e; z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;// - 1.0e-3;
					const auto v2 = p + voxelSize * 0.5;// + 1.0e-3;
					Box3dd smallBox(v1, v2);
					auto particle = new Particle<Triangle3d>(p, triangle);
					table.add(particle);
				}
			}
		}
	}

	//IntersectionCalculator iCalculator;
	for (auto y = space.getMinY(); y < space.getMaxY(); y += res) {
		for (auto z = space.getMinZ(); z < space.getMaxZ(); z += res) {
			const Ray3d ray(Vector3dd(space.getMinX(), y, z), Vector3dd(1, 0, 0));
			for (auto x = space.getMinX(); x < space.getMaxX(); x += res) {
				std::list<double> params;
				const Vector3dd pos(x, y, z);
				if (!table.isEmpty(pos)) {
					const auto ps = table.getParticles(pos);
					for (auto p : ps) {
						auto pt = static_cast<Particle<Triangle3d>*>(p);
						const auto triangle = pt->getAttribute();
						const auto param = IntersectionCalculator::calculateIntersectionParameters(ray, triangle, e);
						if (param.has_value()) {
							params.push_back(param.value().x);
//							const auto i = ray.getPosition(param.value().x);
//							this->intersections.push_back(i);
						}
					}
				}
			}
//			table.isEmpty()
//			IntersectionCalculator::calculateIntersectionParameters()
			/*
			rayTracer.trace(ray, res);
			auto is = rayTracer.getIntersections();
			for (const auto& i : is) {
				this->intersections.push_back(i);
			}
			*/
		}
	}

	/*
	this->voxel = std::make_unique<Voxel>(bb, ress);
	voxel->fill(false);
	for (int i = 0; i < xres; ++i) {
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
	*/

	for (auto p : particles) {
		delete p;
	}

}
