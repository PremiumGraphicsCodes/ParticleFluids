#include "ZIndexedSearchAlgo.h"

#include "../../Crystal/Shape/IPoint.h"

using namespace Crystal::Shape;
using namespace Crystal::Search;

namespace {
	/*
	int toMortonIndex3d(int x) {
		x = (x | (x << 16)) & 0x030000FF;
		x = (x | (x << 8))  & 0x0300F00F;
		x = (x | (x << 4))  & 0x030C30C3;
		x = (x | (x << 2))  & 0x09249249;
		return x;
	}
	*/

	int toMortonIndex2d(int n) {
		n = (n | (n << 16)) & 0b00000000000000001111111111111111;// 0x0000ffff;
		n = (n | (n << 8))  & 0b00000000111111110000000011111111;//0x0000ff00ff;
		n = (n | (n << 4))  & 0b00001111000011110000111100001111;//0x0f0f0f0f;
		n = (n | (n << 2))  & 0b00110011001100110011001100110011;//0x03333333;
		n = (n | (n << 1))  & 0b01010101010101010101010101010101;//0x000055555555;
		return n;
	}
}

ZIndexedSearchAlgo::ZIndexedSearchAlgo(const double searchRadius) :
	searchRadius(searchRadius)
{}

void ZIndexedSearchAlgo::add(IPoint* point)
{
	const auto position = point->getPosition();
	const auto ix = static_cast<int>( position.x / searchRadius );
	const auto iy = static_cast<int>( position.y / searchRadius );
	const auto iz = static_cast<int>( position.z / searchRadius );
	const auto index = toIndex1d(ix, iy, iz);
	ZIndexedParticle zip(index, point);
	points.push_back(zip);
}

void ZIndexedSearchAlgo::sort()
{
	std::sort(points.begin(), points.end());
}

int ZIndexedSearchAlgo::toIndex1d(unsigned int x, unsigned int y, unsigned int z)
{
	const auto xi = toMortonIndex2d(x);
	const auto yi = toMortonIndex2d(y);
	const auto zi = toMortonIndex2d(z);
	return (xi | (yi << 1) | (zi << 2));
}

/*
std::list<IPoint*> ZIndexedSearchAlgo::findNeighbors(IPoint* searchPoint)
{

}
*/
