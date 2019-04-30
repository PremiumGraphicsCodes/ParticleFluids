#pragma once

#include "../../Crystal/Shape/ParticleSystem.h"

namespace Crystal {
	namespace Algo {

struct Volume
{

};

class VolumeConverter
{
public:
	void convert(const Math::Box3d& space, const Shape::ParticleSystem<double>& particleSystem, const int levelOfDetail);

private:
};
	}
}