#include "VolumeConvertAlgo.h"

#include "Octree.h"
#include "../../Crystal/Math/Gaussian.h"
#include "../CrystalAlgo/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Search;
using namespace Crystal::Algo;

VolumeConvertAlgo::VolumeConvertAlgo(const Box3d& box, const double searchRadius)
{
	//Volume()
}

void VolumeConvertAlgo::build()
{
	Gaussian kernel;

	/*
	const auto& particles = particleSystem.getParticles();
	CompactSpaceHash3d spaceHash(searchRadius, particles.size());
	for (auto p : particles) {
		spaceHash.add(p);
	}

	const auto unum = volume.getUNum();
	const auto vnum = volume.getVNum();
	const auto wnum = volume.getWNum();
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