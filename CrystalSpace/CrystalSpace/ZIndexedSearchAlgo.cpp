#include "ZIndexedSearchAlgo.h"

#include "ZOrderCurve3d.h"

#include "../../Crystal/Shape/IParticle.h"

#include <algorithm>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;

ZIndexedSearchAlgo::ZIndexedSearchAlgo(const double searchRadius, const Vector3dd& minPosition) :
	searchRadius(searchRadius),
	minPosition(minPosition)
{}

void ZIndexedSearchAlgo::add(const Vector3dd& position)
{
	const auto ix = toIndex( position );
	const auto index = curve.encode(ix);
	ZIndexedParticle zip(index, position);
	points.push_back(zip);
}

void ZIndexedSearchAlgo::sort()
{
	//points.sort();
	for (int i = 0; i < points.size(); ++i) {
		points[i].index = i;
	}
	std::sort(points.begin(), points.end());
}

std::list<int> ZIndexedSearchAlgo::findNeighbors(const Math::Vector3dd& position)
{
	//const auto position = points[ix].getPosition();
	const auto index = toIndex(position);

	//auto iter = points.front();
	//std::advance(iter, ix);

	const auto curveStartIndex = curve.encode({ index[0] - 1, index[1] - 1, index[2] - 1 });
	ZIndexedParticle dummyStart(curveStartIndex, Vector3dd(0,0,0));
	const auto rangedFirstIter = std::lower_bound(points.begin(), points.end(), dummyStart);

	const auto curveEndIndex = curve.encode({ index[0] + 1, index[1] + 1, index[2] + 1 });
	ZIndexedParticle dummyEnd(curveEndIndex, Vector3dd(0,0,0));
	const auto rangedEndIter = std::lower_bound(rangedFirstIter, points.end(), dummyEnd);

	std::list<int> results;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			for (int k = -1; k <= 1; ++k) {
				const auto ii = index[0]+i;
				const auto jj = index[1]+j;
				const auto kk = index[2]+k;
				const auto rawIndex = toIndex({ ii, jj, kk });
				const auto curveIndex = curve.encode(rawIndex);
				ZIndexedParticle dummy(curveIndex, Vector3dd(0,0,0));
				auto firstIter = std::lower_bound(rangedFirstIter, rangedEndIter, dummy);
				auto secondIter = std::upper_bound(firstIter, rangedEndIter, dummy);
				for (auto iter = firstIter; iter != secondIter; ++iter) {
					const auto distanceSquared = ::getDistanceSquared(position, iter->getPosition());
					if (distanceSquared < searchRadius * searchRadius) {
						results.push_back(iter->index);
					}
				}
 			}
		}
	}

	return results;
	//std::find(points.begin(), points.end(), [=]
}


std::array<unsigned int,3> ZIndexedSearchAlgo::toIndex(const Vector3dd& position) const
{
	const auto p = position - minPosition;
	const auto ix = static_cast<unsigned int>(p.x / searchRadius) + 1; // avoid negative index.
	const auto iy = static_cast<unsigned int>(p.y / searchRadius) + 1;
	const auto iz = static_cast<unsigned int>(p.z / searchRadius) + 1;

	return { ix, iy, iz };
}