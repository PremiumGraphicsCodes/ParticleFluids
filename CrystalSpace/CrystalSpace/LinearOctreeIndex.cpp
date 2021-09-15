#include "LinearOctreeIndex.h"
#include <cmath>

using namespace Crystal::Space;

LinearOctreeIndex::LinearOctreeIndex(const unsigned int level, const unsigned int number)
{
    const auto start = (std::pow(8, level) - 1) / 7;
    this->index1d = start + number;
}

std::pair<unsigned int, unsigned int> LinearOctreeIndex::getLevelAndNumber() const
{
    unsigned int number = index1d;
    int level = 0;
    // �n�b�V���l���珊������ŏ���Ԃ̃��[�g���I�[�_�[�ɕϊ�
    while (number >= std::pow(8, level)) {
        number -= std::pow(8, level);
        level++;
    }
    return std::make_pair(level, number);
}

LinearOctreeIndex LinearOctreeIndex::getParentIndex() const
{
    const auto levelNumber = getLevelAndNumber();
    const auto parentLevel = levelNumber.first - 1;
    const auto number = levelNumber.second;
    const auto parentNumber = number >> 3;
    return LinearOctreeIndex(parentLevel, parentNumber);
}

unsigned int LinearOctreeIndex::getIndex1d() const
{
    return index1d;
}
