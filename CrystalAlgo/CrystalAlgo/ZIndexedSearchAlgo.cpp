#include "ZIndexedSearchAlgo.h"

#include "ZOrderCurve3d.h"

#include "../../Crystal/Shape/IPoint.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;

ZIndexedSearchAlgo::ZIndexedSearchAlgo(const double searchRadius) :
	searchRadius(searchRadius)
{}

void ZIndexedSearchAlgo::add(IPoint* point)
{
	const auto ix = toIndex( point->getPosition() );
	const ZOrderCurve3d curve;
	const auto index = curve.encode(ix);
	ZIndexedParticle zip(index, point);
	points.push_back(zip);
}

void ZIndexedSearchAlgo::sort()
{
	points.sort();
	//std::sort(points.begin(), points.end());
}

std::list<IPoint*> ZIndexedSearchAlgo::findNeighbors(IPoint* searchPoint)
{
	return {};
	//std::find(points.begin(), points.end(), [=]
}


std::array<unsigned int,3> ZIndexedSearchAlgo::toIndex(const Vector3dd& position) const
{
	const auto ix = static_cast<unsigned int>(position.x / searchRadius);
	const auto iy = static_cast<unsigned int>(position.y / searchRadius);
	const auto iz = static_cast<unsigned int>(position.z / searchRadius);

	return { ix, iy, iz };
}

/*
std::list<IPoint*> ZIndexedSearchAlgo::findNeighbors(IPoint* searchPoint)
{

}
*/
