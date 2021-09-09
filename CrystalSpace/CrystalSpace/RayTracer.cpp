#include "RayTracer.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;


void RayTracer::buildSpace(const PolygonMesh& polygon, const Box3dd& space, const int level)
{
	const auto faces = polygon.getFaces();

	octree.init(space, level);

	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		LinearOctreeItem* item = new LinearOctreeItem(triangle.getBoundingBox());
		octree.add(item);
	}
}

// ref https://riyaaaaasan.hatenablog.com/entry/2018/05/08/224545

std::list<LinearOctreeCell*> RayTracer::trace(const Ray3d& ray)
{
	const auto grid = octree.calculateGridIndex(ray.getOrigin()); // レイの初期位置から空間のグリッド座標を算出
	const auto dir = ray.getDirection();

	// レイ方向ベクトルの符号から1ステップにおけるグリッドの移動データを算出
	std::array<int, 3> gridForward;
	gridForward[0] = (dir.x >= 0.0f ? 1 : -1);
	gridForward[1] = (dir.y >= 0.0f ? 1 : -1);
	gridForward[2] = (dir.z >= 0.0f ? 1 : -1);

	const Vector3dd pos = octree.calculateAABB(grid).getMin(); // 初期位置
	auto nextGrid = grid;
	std::list<LinearOctreeCell*> cells; // 衝突リスト（リストの中身は空間ハッシュ）

	while (octree.getRootSpace().isInside(pos)) {
		/*
		// グリッドから空間ハッシュ算出
		uint32_t number = SpaceOctree::Get3DMortonOrder(grid);

		// 空間ハッシュを、ルート空間まで遡って、衝突リストに格納していく（存在する場合のみ）
		for (int i = 0; i <= factory->GetSplitLevel(); i++) {
			uint32_t idx = static_cast<uint32_t>((number >> i * 3) + PrecomputedConstants::PowNumbers<8, 8>::Get(factory->GetSplitLevel() - i) / 7);
			if (factory->BoxExists(idx)) {
				colliderList.insert(idx);
			}
		}
		*/

		// 次のグリッド
		for (int i = 0; i < 3; ++i) {
			nextGrid[i] = grid[i] + gridForward[i];
		}
		// 次の座標
		const auto nextpos = octree.calculateAABB(grid).getMin();

		/*

		// レイベクトルから、X方向、Y方向、Z方向のグリッドに到達する時のレイベクトルの係数を算出 
		float ax = ray.dir.x != 0.0f ? std::abs((nextpos.x - pos.x) / rayForward.x) : FLT_MAX;
		float ay = ray.dir.y != 0.0f ? std::abs((nextpos.y - pos.y) / rayForward.y) : FLT_MAX;
		float az = ray.dir.z != 0.0f ? std::abs((nextpos.z - pos.z) / rayForward.z) : FLT_MAX;

		// 最短で到達するグリッドの探索
		if (ax < ay && ax < az) {
			pos += rayForward * ax;
			grid.x += gridForward.x;
		}
		else if (ay < ax && ay < az) {
			pos += rayForward * ay;
			grid.y += gridForward.y;
		}
		else if (az < ax && az < ay) {
			pos += rayForward * az;
			grid.z += gridForward.z;
		}
		else {
			pos += rayForward;
			grid += gridForward;
		}
		*/
	}

	return cells;
}
