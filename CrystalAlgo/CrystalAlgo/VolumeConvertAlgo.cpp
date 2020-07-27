#include "VolumeConvertAlgo.h"

#include "Octree.h"
#include "../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Search;
using namespace Crystal::Algo;

VolumeConvertAlgo::VolumeConvertAlgo(const Box3d& box, const double divideLength) : 
	volume(box),
	spaceHash(divideLength, 1000)
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
	spaceHash.add(particle);
}


void VolumeConvertAlgo::build()
{
	Gaussian kernel;


	const auto unum = volume.getUNum();
	const auto vnum = volume.getVNum();
	const auto wnum = volume.getWNum();
	/*
	for (int u = 0; u < unum; ++u) {
		for (int v = 0; v < vnum; ++v) {
			for (int w = 0; w < wnum; ++w) {
				const auto& p = volume.getPosition(u, v, w);
				const auto& neighbors = spaceHash.findNeighbors(p);
				for (auto n : neighbors) {
					const auto distanceSquared = Crystal::Math::getDistanceSquared(p, n->getPosition());
					if (distanceSquared > searchRadius * searchRadius) {
						const auto distance = ::sqrt(distanceSquared);
						const auto value = kernel.getValue(distance / searchRadius) + volume.getValue(u,v,w);
						volume.set(u, v, w, value);
					}
				}
			}
		}
	}
	*/
}