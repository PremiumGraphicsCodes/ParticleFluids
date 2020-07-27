#pragma once

#include "../../Crystal/Scene/VolumeScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace Algo {

class VolumeConvertAlgo
{
public:
	VolumeConvertAlgo(const Math::Box3d& box, const double divideLength);

	void add(Shape::IPoint* particle);

	void build();

private:
	//Volume volume;
};
	}
}