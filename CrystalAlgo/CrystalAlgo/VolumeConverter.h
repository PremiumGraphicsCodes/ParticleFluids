#pragma once

#include "Volume3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

class VolumeConverter
{
public:
	void convert(Volume3d& volume, const Shape::ParticleSystem<double>& particleSystem, const double searchRadius);

private:
};
	}
}