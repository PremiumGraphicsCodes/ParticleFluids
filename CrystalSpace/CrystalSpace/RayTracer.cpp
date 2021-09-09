#include "RayTracer.h"
#include "SpaceHash3d.h"
#include "Octree.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;

namespace {
	const auto e = 1.0e-12;

	/*
	class FaceItem : public IOctreeItem
	{
	public:
		explicit FaceItem(const Face& f) :
			IOctreeItem(f.ge)
			f(f)
		{
		}

		Box3dd getBoundingBox() override
		{
			return box;
		}

	private:
		Face f;
	};
	*/
}


void RayTracer::buildSpace(const PolygonMesh& polygon, const double res)
{
	const auto bb = polygon.getBoundingBox();
	const auto xres = static_cast<size_t>(bb.getLength().x / res) + 1;
	const auto yres = static_cast<size_t>(bb.getLength().y / res) + 1;
	const auto zres = static_cast<size_t>(bb.getLength().z / res) + 1;
	std::array<size_t, 3> ress = { xres, yres, zres };

	const auto faces = polygon.getFaces();
	SpaceHash3d table(res, faces.size() * 3);

	const auto voxelSize = Vector3dd(res);
	Octree octree(bb, 0);

	std::vector<IParticle*> particles;
	for (const auto& f : faces) {
		const auto triangle = f.toTriangle(polygon.getPositions());
		if (triangle.getArea() < e) {
			continue;
		}
		const auto smallBB = triangle.getBoundingBox();
		//auto item = new FaceItem(smallBB);
		//octree.add(item);

		/*
		for (float x = smallBB.getMinX(); x < smallBB.getMaxX() + e; x += voxelSize.x) {
			for (float y = smallBB.getMinY(); y < smallBB.getMaxY() + e; y += voxelSize.y) {
				for (float z = smallBB.getMinZ(); z < smallBB.getMaxZ() + e; z += voxelSize.z) {
					const Vector3dd p(x, y, z);
					const auto v1 = p - voxelSize * 0.5;// - 1.0e-3;
					const auto v2 = p + voxelSize * 0.5;// + 1.0e-3;
					Box3dd smallBox(v1, v2);
					if (Overlap::overlap(smallBox, triangle)) {
						particles.push_back(particle);
						table.add(particle);
					}
				}
			}
		}
		*/
	}
}

// ref https://riyaaaaasan.hatenablog.com/entry/2018/05/08/224545

std::list<LinearOctree*> RayTracer::trace(const Ray3d& ray)
{
	const auto grid = octree.calculateGridIndex(ray.getOrigin()); // レイの初期位置から空間のグリッド座標を算出
	const auto dir = ray.getDirection();
	std::array<int, 3> gridForward;
	// レイ方向ベクトルの符号から1ステップにおけるグリッドの移動データを算出
	gridForward[0] = (dir.x >= 0.0f ? 1 : -1);
	gridForward[1] = (dir.y >= 0.0f ? 1 : -1);
	gridForward[2] = (dir.z >= 0.0f ? 1 : -1);

	const Vector3dd pos = octree.calculateAABB(grid).getMin(); // 初期位置
	auto nextGrid = grid;
	std::list<LinearOctree*> cells; // 衝突リスト（リストの中身は空間ハッシュ）

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
		/*
		// 次の座標
		Vector3D nextpos = Vector3D(nextGrid.x * size.w, nextGrid.y * size.h, nextGrid.z * size.h) + rootAABB.bpos;

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
