#pragma once

#include "../../Crystal/Scene/ParticleSystemScene.h"
#include "../../Crystal/Scene/IAnimator.h"
#include "TimeSeriesParticleSystemReader.h"

namespace Crystal {
	namespace Physics {

class TimeSeriesParticleSystemAnimator : public Scene::IAnimator
{
public:
	TimeSeriesParticleSystemAnimator();

	void setScene(Scene::ParticleSystemScene* scene) { this->scene = scene; }

	void setReader(TimeSeriesParticleSystemReader* reader) { this->reader = reader; }

	void reset();

	void step();

	void stop() { this->stop_ = true; }

	void start() { this->stop_ = false; }

private:
	Scene::ParticleSystemScene* scene;
	TimeSeriesParticleSystemReader* reader;
	bool stop_;
};
	}
}