#pragma once

#include "Volume.h"
#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

class VolumeConverter
{
public:
	void convert(Volume& volume, const Shape::ParticleSystem<double>& particleSystem, const double searchRadius);

private:
};
	}
}