#pragma once

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/IAnimator.h"
#include "TimeSeriesParticleSystemReader.h"

namespace Crystal {
	namespace Physics {

class TimeSeriesParticleSystemAnimator : public Scene::IAnimator
{
public:
	TimeSeriesParticleSystemAnimator(Scene::ParticleSystemScene* particleSystem, TimeSeriesParticleSystemReader* reader);

	void step();

private:
	Scene::ParticleSystemScene* particleSystem;
	TimeSeriesParticleSystemReader* reader;
};
	}
}