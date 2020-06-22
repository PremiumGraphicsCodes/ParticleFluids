#include "ZIndexedSearchAlgo.h"

#include "ZOrderCurve3d.h"

#include "../../Crystal/Shape/IPoint.h"

using namespace Crystal::Shape;
using namespace Crystal::Search;


ZIndexedSearchAlgo::ZIndexedSearchAlgo(const double searchRadius) :
	searchRadius(searchRadius)
{}

void ZIndexedSearchAlgo::add(IPoint* point)
{
	const auto position = point->getPosition();
	const auto ix = static_cast<int>( position.x / searchRadius );
	const auto iy = static_cast<int>( position.y / searchRadius );
	const auto iz = static_cast<int>( position.z / searchRadius );
	const auto index = ZOrderCurve3d::encode({ ix, iy, iz });
	ZIndexedParticle zip(index, point);
	points.push_back(zip);
}

void ZIndexedSearchAlgo::sort()
{
	std::sort(points.begin(), points.end());
}

/*
int ZIndexedSearchAlgo::toIndex1d(unsigned int x, unsigned int y, unsigned int z)
{
	const auto xi = ZOrderCurve::toMortonIndex2d(x);
	const auto yi = ZOrderCurve::toMortonIndex2d(y);
	const auto zi = ZOrderCurve::toMortonIndex2d(z);
	return (xi | (yi << 1) | (zi << 2));
}

/*
std::list<IPoint*> ZIndexedSearchAlgo::findNeighbors(IPoint* searchPoint)
{

}
*/
