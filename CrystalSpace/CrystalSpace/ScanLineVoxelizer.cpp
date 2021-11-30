#include "ScanLineVoxelizer.h"

#include "../../Crystal/Shape/TriangleMesh.h"
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
	const auto e = 1.0e-18;
}

void ScanLineVoxelizer::voxelize(const std::vector<Triangle3d>& triangles, const Box3dd& space, const double res)
{
	const auto xres = static_cast<size_t>(space.getLength().x / res) + 1;
	const auto yres = static_cast<size_t>(space.getLength().y / res) + 1;
	const auto zres = static_cast<size_t>(space.getLength().z / res) + 1;
	std::array<size_t, 3> ress = { xres, yres, zres };

	const int size = static_cast<int>( triangles.size() * 3 );
	SpaceHash3d table(res, size);

	const auto cellLength = Vector3dd(res);

	std::vector<Particle<Triangle3d>*> particles;
	for (const auto& triangle : triangles) {
		const auto smallBB = triangle.getBoundingBox();

		for (auto x = smallBB.getMinX(); x < smallBB.getMaxX() + res + e; x += res) {
			for (auto y = smallBB.getMinY(); y < smallBB.getMaxY() + res + e; y += res) {
				for (auto z = smallBB.getMinZ(); z < smallBB.getMaxZ() + res + e; z += res) {
					const Vector3dd p(x, y, z);
					auto particle = new Particle<Triangle3d>(p, triangle);
					table.add(particle);
				}
			}
		}
	}

	Array3d<unsigned int> array3d(ress, 0);
	const auto& resolutions = array3d.getResolutions();

	//const Ray3d ray(Vector3dd(0, 5, 5), Vector3dd(1, 0, 0));
	for (size_t j = 0; j < yres; ++j) {
		const auto y = space.getMinY() + j * cellLength.y;
		for (size_t k = 0; k < zres; ++k) {
			const auto z = space.getMinZ() + k * cellLength.z;
			const Ray3d ray(Vector3dd(space.getMinX(), y, z), Vector3dd(1, 0, 0));
			std::list<double> params;
			for (size_t i = 0; i < xres; ++i) {
				const auto x = space.getMinX() + i * cellLength.x;
				const Vector3dd pos(x, y, z);
				if (!table.isEmpty(pos)) {
					const auto ps = table.getParticles(pos);
					for (auto p : ps) {
						auto pt = static_cast<Particle<Triangle3d>*>(p);
						const auto triangle = pt->getAttribute();
						const auto param = IntersectionCalculator::calculateIntersectionParameters(ray, triangle, e);
						if (param.has_value()) {
							params.push_back(param.value().x);
							const auto is = ray.getPosition(param.value().x);
							this->intersections.push_back(is);
							auto v = array3d.get(i, j, k);
						}
					}
				}
				params.sort();
				params.unique([](auto p1, auto p2) { return std::fabs(p1 - p2) < 1.0e-6; });
				array3d.set(i, j, k, params.size());
			}
		}
	}

	this->voxel = std::make_unique<Voxel>(space, ress);
	voxel->fill(false);
	for (int i = 0; i < xres; ++i) {
		for (int j = 0; j < yres; ++j) {
			for (int k = 0; k < zres; ++k) {
				if (array3d.get(i, j, k) % 2 == 1) {
					voxel->setValue(i, j, k, true);
				}
			}
		}
	}

	for (auto p : particles) {
		delete p;
	}

}
