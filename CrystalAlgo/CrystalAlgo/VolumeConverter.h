#pragma once

#include "Volume3d.h"
#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

class VolumeConverter
{
public:
	void convert(const Volume3d& volume, const Shape::ParticleSystem<double>& particleSystem);

private:
};
	}
}