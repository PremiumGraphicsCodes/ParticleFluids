#pragma once

#include "../../Crystal/Shape/Volume.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "CompactSpaceHash3d.h"

namespace Crystal {
	namespace Algo {

class VolumeConvertAlgo
{
public:
	VolumeConvertAlgo(const Math::Box3d& box, const double divideLength);

	void add(Shape::IParticle* particle);

	void build();

private:
	Shape::Volume<double> volume;
	Search::CompactSpaceHash3d spaceHash;
};
	}
}