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

    //auto ii = ZOrderCurve3d::decode(n);

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
    const auto parentCode = toIndex(bb);
    if (this->tree[parentCode] == nullptr) {
        this->tree[parentCode] = std::make_unique<LinearOctree>();
    }
    this->tree[parentCode]->add( item );
}

std::list<IOctreeItem*> LinearOctreeOperator::findItems(const Box3dd& space)
{
    const auto parentCode = toIndex(space);
    if (this->tree[parentCode] == nullptr) {
        return {};
    }
    return this->tree[parentCode]->getItems();
}

unsigned int LinearOctreeOperator::toIndex(const Box3dd& space) const
{
    const auto i1 = calculateGridIndex(space.getMin());
    const auto i2 = calculateGridIndex(space.getMax());
    const auto e1 = ZOrderCurve3d::encode(i1);
    const auto e2 = ZOrderCurve3d::encode(i2);
    return ZOrderCurve3d::getParent(e1, e2);
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