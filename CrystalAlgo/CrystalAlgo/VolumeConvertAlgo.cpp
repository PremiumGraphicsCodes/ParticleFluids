#include "VolumeConvertAlgo.h"
#include "CompactSpaceHash3d.h"

#include "Octree.h"
#include "../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Search;
using namespace Crystal::Algo;

VolumeConvertAlgo::VolumeConvertAlgo(const Box3d& box, const double divideLength) : 
	volume(box)
{
	const auto& length = box.getLength();
	const auto xnum = static_cast<int>( length.x / divideLength );
	const auto ynum = static_cast<int>( length.y / divideLength );
	const auto znum = static_cast<int>( length.z / divideLength );
	volume.build(xnum, ynum, znum);
	//Volume()
}

void VolumeConvertAlgo::add(IParticle* particle)
{
	particles.push_back(particle);
}

void VolumeConvertAlgo::build(const double searchRadius)
{
	Gaussian kernel;

	CompactSpaceHash3d spaceHash(searchRadius, particles.size());

	const auto unum = volume.getUNum();
	const auto vnum = volume.getVNum();
	const auto wnum = volume.getWNum();

	for (int u = 0; u < unum; ++u) {
		for (int v = 0; v < vnum; ++v) {
			for (int w = 0; w < wnum; ++w) {
				const auto& p = volume.getCellPosition(u, v, w);
				const auto& neighbors = spaceHash.findNeighbors(p);
				for (auto n : neighbors) {
					const auto distanceSquared = Crystal::Math::getDistanceSquared(p, n->getPosition());
					if (distanceSquared > searchRadius * searchRadius) {
						const auto distance = ::sqrt(distanceSquared);
						const auto value = kernel.getValue(distance / searchRadius) + volume.getValue(u,v,w);
						volume.setValue(u, v, w, value);
					}
				}
			}
		}
	}
}