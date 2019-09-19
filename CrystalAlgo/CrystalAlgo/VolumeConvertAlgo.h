#pragma once

#include "../../Crystal/Scene/VolumeScene.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace Algo {

class VolumeConvertAlgo
{
public:
	void convert(Scene::Volume& volume, const Scene::ParticleSystem<double>& particleSystem, const double searchRadius);

private:
};
	}
}