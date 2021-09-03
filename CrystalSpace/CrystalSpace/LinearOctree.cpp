#include "LinearOctree.h"

#include <list>

#include "../../Crystal/Math/Box3d.h"
#include "ZOrderCurve3d.h"

// reference https://riyaaaaasan.hatenablog.com/entry/2018/03/28/233511

using namespace Crystal::Math;
using namespace Crystal::Space;

Box3dd LinearOctreeOperator::calculateAABBFromMortonNumber(const unsigned int n)
{
    unsigned int number = n;
    int level = 0;
    // ハッシュ値から所属する最小空間のモートンオーダーに変換
    while (number >= std::pow(8, level)) {
        number -= std::pow(8, level);
        level++;
    }

    uint32_t s = 0;

    for (int i = level; i > 0; i--) {
        s = s | (number >> (3 * i - 2 - i) & (1 << i - 1));
    }
    uint32_t x = s;

    s = 0;
    for (int i = level; i > 0; i--) {
        s = s | (number >> (3 * i - 1 - i) & (1 << i - 1));
    }
    uint32_t y = s;

    s = 0;
    for (int i = level; i > 0; i--) {
        s = s | (number >> (3 * i - i) & (1 << i - 1));
    }
    uint32_t z = s;

    // _rootAABB.size: ルート空間のサイズ。空間レベルで割って所属する空間レベルの分割サイズを求める
    const auto boxSize = rootSpace.getLength() / static_cast<double>(1 << level);
    // _rootAABB.bpos: ルート空間の開始座標
    Vector3dd bpos = Vector3dd(x * boxSize.x, y * boxSize.y, z * boxSize.z) + rootSpace.getMin();
    // 所属するAABB
    return Box3dd(bpos, Vector3dd(bpos.x + boxSize.x, bpos.y + boxSize.y, bpos.z + boxSize.z));
}

/*
std::list<uint32_t> GetColliderMortonList(SpaceOctree::OctreeFactoryBase* factory, Ray ray) {
    auto size = factory->GetMinBoxSize(); // 最大の空間レベルの分割サイズ
    auto rayForward = Vector3D(ray.dir.x * size.w, ray.dir.y * size.h, ray.dir.z * size.d); // レイが1ステップに進む距離
    auto rootAABB = factory->GetRootAABB(); // ルート空間

    _Vector3D<int16_t> grid = factory->CalculateGridCoordinate(ray.pos); // レイの初期位置から空間のグリッド座標を算出
    _Vector3D<int8_t> gridForward = _Vector3D<int8_t>( // レイ方向ベクトルの符号から1ステップにおけるグリッドの移動データを算出
        ray.dir.x >= 0.0f ? 1 : -1,
        ray.dir.y >= 0.0f ? 1 : -1,
        ray.dir.z >= 0.0f ? 1 : -1
        );

    Vector3D pos = Vector3D(grid.x * size.w, grid.y * size.h, grid.z * size.h) + rootAABB.bpos; // 初期位置
    _Vector3D<int16_t> nextGrid = grid;
    std::set<uint32_t> colliderList; // 衝突リスト（リストの中身は空間ハッシュ）

    while (rootAABB.Contains(pos)) {
        // グリッドから空間ハッシュ算出
        uint32_t number = SpaceOctree::Get3DMortonOrder(grid);

        // 空間ハッシュを、ルート空間まで遡って、衝突リストに格納していく（存在する場合のみ）
        for (int i = 0; i <= factory->GetSplitLevel(); i++) {
            uint32_t idx = static_cast<uint32_t>((number >> i * 3) + PrecomputedConstants::PowNumbers<8, 8>::Get(factory->GetSplitLevel() - i) / 7);
            if (factory->BoxExists(idx)) {
                colliderList.insert(idx);
            }
        }

        // 次のグリッド
        nextGrid = grid + gridForward;
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
    }

    return colliderList;
}
*/

void LinearOctreeOperator::init(const Math::Box3dd& box, const int level)
{
    int current = 1;
    for (int i = 1; i < level + 1; i++){
        current = current * 8;
    }
    const auto size = (current - 1) / 7;
    tree.resize(size);
}

void LinearOctreeOperator::add(IOctreeItem* item)
{
    const auto bb = item->getBoundingBox();
   // bb.getMin() / minWidth;
    ZOrderCurve3d mortonCode;
    //if(mortonCode.getParent()
}
