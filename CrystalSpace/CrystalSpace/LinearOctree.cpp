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

Box3dd Crystal::Space::LinearOctreeOperator::calculateAABBFromIndices(const std::array<unsigned int, 3>& indices) const
{
    const auto size = this->getMinBoxSize(); // �ő�̋�ԃ��x���̕����T�C�Y
    Vector3dd v1(indices[0] * size.x, indices[1] * size.y, indices[2] * size.z);
    v1 += rootSpace.getMin();
    const Vector3dd v2 = v1 + size;
    return Math::Box3dd(v1, v2);
}

std::list<IOctreeItem*> Crystal::Space::LinearOctreeOperator::findCollisions(const Math::Ray3d& ray)
{
    const auto size = this->getMinBoxSize(); // �ő�̋�ԃ��x���̕����T�C�Y
    Vector3dd rayForward = ray.getDirection() + size;
    auto rootAABB = this->rootSpace; // ���[�g���

    auto gridIndex = calculateGridIndex(ray.getOrigin());
    std::array<short int, 3> gridForward;
    gridForward[0] = ray.getDirection().x >= 0.0 ? 1.0 : -1.0;
    gridForward[1] = ray.getDirection().y >= 0.0 ? 1.0 : -1.0;
    gridForward[2] = ray.getDirection().z >= 0.0 ? 1.0 : -1.0;

    Vector3dd pos(gridIndex[0] * size.x, gridIndex[1] * size.y, gridIndex[2] * size.z);
    pos += rootAABB.getMin();

    auto nextGridIndex = gridIndex;
    
    std::list<IOctreeItem*> colliderList; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

    while (rootAABB.isInside(pos)) {
        // �O���b�h�����ԃn�b�V���Z�o
        ZOrderCurve3d mortonOrder;
        const auto number = mortonOrder.encode(gridIndex);
        
        // ��ԃn�b�V�����A���[�g��Ԃ܂ők���āA�Փ˃��X�g�Ɋi�[���Ă����i���݂���ꍇ�̂݁j
        //for (int i = 0; i <= factory->GetSplitLevel(); i++) {
        /*
        for(int i = 0; i < 8; ++i) {
            uint32_t idx = static_cast<uint32_t>((number >> i * 3) + PrecomputedConstants::PowNumbers<8, 8>::Get(factory->GetSplitLevel() - i) / 7);
            if (factory->BoxExists(idx)) {
                colliderList.insert(idx);
            }
        }
        */
        
        // ���̃O���b�h
        for (int i = 0; i < 3; ++i) {
            nextGridIndex[i] = gridIndex[i] + gridForward[i];
        }
        
        // ���̍��W
        Vector3dd nextpos = Vector3dd(nextGridIndex[0] * size.x, nextGridIndex[1] * size.y, nextGridIndex[2] * size.z) + rootAABB.getMin();
        
        // ���C�x�N�g������AX�����AY�����AZ�����̃O���b�h�ɓ��B���鎞�̃��C�x�N�g���̌W�����Z�o
        double ax = ray.getDirection().x != 0.0f ? std::abs((nextpos.x - pos.x) / rayForward.x) : FLT_MAX;
        double ay = ray.getDirection().y != 0.0f ? std::abs((nextpos.y - pos.y) / rayForward.y) : FLT_MAX;
        double az = ray.getDirection().z != 0.0f ? std::abs((nextpos.z - pos.z) / rayForward.z) : FLT_MAX;
        
        // �ŒZ�œ��B����O���b�h�̒T��
        if (ax < ay && ax < az) {
            pos += rayForward * ax;
            gridIndex[0] += gridForward[0];
        }
        else if (ay < ax && ay < az) {
            pos += rayForward * ay;
            gridIndex[1] += gridForward[1];
        }
        else if (az < ax && az < ay) {
            pos += rayForward * az;
            gridIndex[2] += gridForward[2];
        }
        else {
            pos += rayForward;
            for (int i = 0; i < 3; ++i) {
                gridIndex[i] += gridForward[i];
            }
        }
    }
    return colliderList;
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
    const auto e1 = ZOrderCurve3d::encode(i1);
    const auto e2 = ZOrderCurve3d::encode(i2);
    const auto parentCode = ZOrderCurve3d::getParent(e1, e2);
    if (this->tree[parentCode] == nullptr) {
        this->tree[parentCode] = std::make_unique<LinearOctree>();
    }
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