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
    // �n�b�V���l���珊������ŏ���Ԃ̃��[�g���I�[�_�[�ɕϊ�
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

    // _rootAABB.size: ���[�g��Ԃ̃T�C�Y�B��ԃ��x���Ŋ����ď��������ԃ��x���̕����T�C�Y�����߂�
    const auto boxSize = rootSpace.getLength() / static_cast<double>(1 << level);
    // _rootAABB.bpos: ���[�g��Ԃ̊J�n���W
    Vector3dd bpos = Vector3dd(x * boxSize.x, y * boxSize.y, z * boxSize.z) + rootSpace.getMin();
    // ��������AABB
    return Box3dd(bpos, Vector3dd(bpos.x + boxSize.x, bpos.y + boxSize.y, bpos.z + boxSize.z));
}

std::list<IOctreeItem*> Crystal::Space::LinearOctreeOperator::findCollisions(const Math::Ray3d& ray)
{
    const auto size = this->getMinBoxSize(); // �ő�̋�ԃ��x���̕����T�C�Y
    const Vector3dd rayForward = ray.getDirection() + size;
    auto rootAABB = this->rootSpace; // ���[�g���

    const auto gridIndex = calculateGridIndex(ray.getOrigin());
    std::array<short int, 3> gridForward;
    gridForward[0] = ray.getDirection().x >= 0.0 ? 1.0 : -1.0;
    gridForward[1] = ray.getDirection().y >= 0.0 ? 1.0 : -1.0;
    gridForward[2] = ray.getDirection().z >= 0.0 ? 1.0 : -1.0;

    Vector3dd pos(gridIndex[0] * size.x, gridIndex[1] * size.y, gridIndex[2] * size.z);
    pos += rootAABB.getMin();

    auto nextGridIndex = gridIndex;
    
    std::list<IOctreeItem*> colliderList; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

    /*
    while (rootAABB.isInside(pos)) {
        // �O���b�h�����ԃn�b�V���Z�o
    uint32_t number = SpaceOctree::Get3DMortonOrder(grid);

    // ��ԃn�b�V�����A���[�g��Ԃ܂ők���āA�Փ˃��X�g�Ɋi�[���Ă����i���݂���ꍇ�̂݁j
    for (int i = 0; i <= factory->GetSplitLevel(); i++) {
        uint32_t idx = static_cast<uint32_t>((number >> i * 3) + PrecomputedConstants::PowNumbers<8, 8>::Get(factory->GetSplitLevel() - i) / 7);
        if (factory->BoxExists(idx)) {
            colliderList.insert(idx);
        }
    }

    // ���̃O���b�h
    nextGrid = grid + gridForward;
    // ���̍��W
    Vector3D nextpos = Vector3D(nextGrid.x * size.w, nextGrid.y * size.h, nextGrid.z * size.h) + rootAABB.bpos;

    // ���C�x�N�g������AX�����AY�����AZ�����̃O���b�h�ɓ��B���鎞�̃��C�x�N�g���̌W�����Z�o
    float ax = ray.dir.x != 0.0f ? std::abs((nextpos.x - pos.x) / rayForward.x) : FLT_MAX;
    float ay = ray.dir.y != 0.0f ? std::abs((nextpos.y - pos.y) / rayForward.y) : FLT_MAX;
    float az = ray.dir.z != 0.0f ? std::abs((nextpos.z - pos.z) / rayForward.z) : FLT_MAX;

    // �ŒZ�œ��B����O���b�h�̒T��
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
*/

    return std::list<IOctreeItem*>();
}

void LinearOctreeOperator::init(const Math::Box3dd& box, const int level)
{
    this->rootSpace = box;
    this->maxLevel = level;
    const auto size = (std::pow(8,level+1) - 1) / 7;
    tree.resize(size);
}

void LinearOctreeOperator::add(IOctreeItem* item)
{
    const auto bb = item->getBoundingBox();
    const auto i1 = calculateGridIndex(bb.getMin());
    const auto i2 = calculateGridIndex(bb.getMax());
    ZOrderCurve3d mortonCode;
    const auto e1 = mortonCode.encode(i1);
    const auto e2 = mortonCode.encode(i2);
    const auto parentCode = mortonCode.getParent(e1, e2);
    this->tree[parentCode]->add( item );
}

Vector3dd LinearOctreeOperator::getMinBoxSize() const
{
    return this->rootSpace.getLength() / std::pow(2.0, this->maxLevel);
}

std::array<unsigned int, 3> LinearOctreeOperator::calculateGridIndex(const Vector3dd& pos) const
{
    const auto p = pos - this->rootSpace.getMin();
    const auto size = getMinBoxSize();
    const auto ix = static_cast<unsigned int>(p.x / size.x);
    const auto iy = static_cast<unsigned int>(p.y / size.y);
    const auto iz = static_cast<unsigned int>(p.z / size.z);
    return { ix, iy, iz };
}