#include "RayTracer.h"

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

std::list<const LinearOctreeCell*> RayTracer::trace(const Ray3d& ray, const double pitch)
{
	//const auto grid = octree.calculateGridIndex(ray.getOrigin()); // レイの初期位置から空間のグリッド座標を算出
	const auto dir = glm::normalize(ray.getDirection());

	Vector3dd pos = ray.getOrigin(); // 初期位置
	std::list<const LinearOctreeCell*> cells; // 衝突リスト（リストの中身は空間ハッシュ）

	double length = 0.0;
	while (octree.getRootSpace().isInside(pos)) {
		const auto nextPos = pos + dir * pitch;
		auto index = octree.getIndex(Box3dd(pos, nextPos));
		auto level = index.getLevelAndNumber().first;
		while (level >= 0) {
			auto cell = octree.findCell(index);
			if (cell != nullptr) {
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

	return cells;
}

/*
std::list<const LinearOctreeCell*> RayTracer::traceLv0(const Ray3d& ray, const double pitch)
{
	octree.findCell(LinearOctreeIndex)
}
*/