#pragma once

#include "../../Crystal/Shape/Volume.h"
#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

class VolumeConvertAlgo
{
public:
	void convert(Shape::Volume& volume, const Shape::ParticleSystem<double>& particleSystem, const double searchRadius);

private:
};
	}
}