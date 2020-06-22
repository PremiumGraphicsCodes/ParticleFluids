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
	const auto index = toIndex(searchPoint->getPosition());
	std::list<IPoint*> results;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				const auto ii = index[0]+i;
				const auto jj = index[1]+j;
				const auto kk = index[2]+k;
				const auto rawIndex = toIndex({ ii, jj, kk });
				const auto curveIndex = curve.encode(rawIndex);
				ZIndexedParticle dummy(curveIndex, nullptr);
				auto firstIter = std::lower_bound(points.begin(), points.end(), dummy);
				auto secondIter = std::upper_bound(firstIter, points.end(), dummy);
				for (auto iter = firstIter; iter != secondIter; ++iter) {
					results.push_back(iter->getPoint());
				}
 			}
		}
	}

	return results;
	//std::find(points.begin(), points.end(), [=]
}


std::array<unsigned int,3> ZIndexedSearchAlgo::toIndex(const Vector3dd& position) const
{
	const auto ix = static_cast<unsigned int>(position.x / searchRadius);
	const auto iy = static_cast<unsigned int>(position.y / searchRadius);
	const auto iz = static_cast<unsigned int>(position.z / searchRadius);

	return { ix, iy, iz };
}