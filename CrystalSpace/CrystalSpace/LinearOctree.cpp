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

/*
std::list<uint32_t> GetColliderMortonList(SpaceOctree::OctreeFactoryBase* factory, Ray ray) {
    auto size = factory->GetMinBoxSize(); // �ő�̋�ԃ��x���̕����T�C�Y
    auto rayForward = Vector3D(ray.dir.x * size.w, ray.dir.y * size.h, ray.dir.z * size.d); // ���C��1�X�e�b�v�ɐi�ދ���
    auto rootAABB = factory->GetRootAABB(); // ���[�g���

    _Vector3D<int16_t> grid = factory->CalculateGridCoordinate(ray.pos); // ���C�̏����ʒu�����Ԃ̃O���b�h���W���Z�o
    _Vector3D<int8_t> gridForward = _Vector3D<int8_t>( // ���C�����x�N�g���̕�������1�X�e�b�v�ɂ�����O���b�h�̈ړ��f�[�^���Z�o
        ray.dir.x >= 0.0f ? 1 : -1,
        ray.dir.y >= 0.0f ? 1 : -1,
        ray.dir.z >= 0.0f ? 1 : -1
        );

    Vector3D pos = Vector3D(grid.x * size.w, grid.y * size.h, grid.z * size.h) + rootAABB.bpos; // �����ʒu
    _Vector3D<int16_t> nextGrid = grid;
    std::set<uint32_t> colliderList; // �Փ˃��X�g�i���X�g�̒��g�͋�ԃn�b�V���j

    while (rootAABB.Contains(pos)) {
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
