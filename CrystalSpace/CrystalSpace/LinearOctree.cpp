#include "LinearOctree.h"

#include "../../Crystal/Math/Box3d.h"

// reference https://riyaaaaasan.hatenablog.com/entry/2018/03/28/233511

using namespace Crystal::Math;
using namespace Crystal::Space;

Box3dd LinearOctree::CalculateOctreeBoxAABBFromMortonNumber(const unsigned int n)
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
    const auto boxSize = space.getLength() / static_cast<double>(1 << level);
    // _rootAABB.bpos: ���[�g��Ԃ̊J�n���W
    Vector3dd bpos = Vector3dd(x * boxSize.x, y * boxSize.y, z * boxSize.z) + space.getMin();
    // ��������AABB
    return Box3dd(bpos, Vector3dd(bpos.x + boxSize.x, bpos.y + boxSize.y, bpos.z + boxSize.z));
}