#include "RayTracer.h"

#include "IntersectionCalculator.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;


void RayTracer::build(const Box3dd& space, const int level)
{
	octree.init(space, level);
}

void RayTracer::add(RayTraceItem* item)
{
	octree.add(item);
}

// ref https://riyaaaaasan.hatenablog.com/entry/2018/05/08/224545

void RayTracer::trace(const Ray3d& ray, const double pitch)
{
	const auto dir = glm::normalize(ray.getDirection());

	Vector3dd pos = ray.getOrigin();
	std::list<const LinearOctreeCell*> cells;

	double length = 0.0;
	while (octree.getRootSpace().isInside(pos)) {
		const auto nextPos = pos + dir * pitch;
		auto index = octree.getIndex(Box3dd(pos, nextPos));
		auto level = index.getLevelAndNumber().first;
		while (level >= 0) {
			auto cell = octree.findCell(index);
			if (cell != nullptr) {
				indices.push_back(index);
				cells.push_back(cell);
			}
			if (level == 0) {
				break;
			}
			index = index.getParentIndex();
			level = index.getLevelAndNumber().first;
		}

		pos = nextPos;
		length += pitch;
	}

	indices.sort();
	indices.unique();
	cells.sort();
	cells.unique();
	findCollisions(ray);
}

void RayTracer::findCollisions(const Ray3d& ray)
{
	IntersectionCalculator calculator;
	for (auto cell : cells) {
		const auto items = cell->getItems();
		for (auto item : items) {
			auto rtItem = static_cast<RayTraceItem*>(item);
			const auto t = rtItem->getTriangle();
			calculator.calculateIntersection(ray, t, 1.0e-12);
		}
	}
	const auto intersections = calculator.getIntersections();
	for (auto i : intersections) {
		this->collisions.push_back(i.position);
	}
}
