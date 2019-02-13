#include "SpaceHash.h"
#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Algo;

SpaceHash::SpaceHash(const float divideLength, const int tableSize) :
	divideLength(divideLength),
	tableSize(tableSize)
{}

std::array<int,3> SpaceHash::toIndex(const Vector3df& pos)
{
	const int ix = static_cast<int>((pos[0]) / divideLength);
	const int iy = static_cast<int>((pos[1]) / divideLength);
	const int iz = static_cast<int>((pos[2]) / divideLength);
	return{ ix, iy, iz };
}

int SpaceHash::toHash(const Vector3df& pos)
{
	return toHash(toIndex(pos));
}

int SpaceHash::toHash(const std::array<int,3>& index)
{
	std::bitset<32> x = index[0] * p1;
	std::bitset<32> y = index[1] * p2;
	std::bitset<32> z = index[2] * p3;
	//assert(x >= 0);
	//assert(y >= 0);
	//assert(z >= 0);
	const auto value = (x ^ y ^ z).to_ulong();
	return value % tableSize;
}