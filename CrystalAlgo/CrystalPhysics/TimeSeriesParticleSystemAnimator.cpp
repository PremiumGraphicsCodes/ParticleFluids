#include "TimeSeriesParticleSystemAnimator.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;


TimeSeriesParticleSystemAnimator::TimeSeriesParticleSystemAnimator() :
	scene(nullptr),
	reader(nullptr),
	stop_(false)
{}

void TimeSeriesParticleSystemAnimator::reset()
{
	//reader->reset();
}

void TimeSeriesParticleSystemAnimator::step()
{
	if (stop_) {
		return;
	}
	reader->step();

	const auto positions = reader->getPositions();

	auto particleSystem = scene->getShape();
	ParticleAttribute attr;
	attr.color = Crystal::Graphics::ColorRGBAf(1.0f, 1.0f, 1.0f, 1.0f);
	attr.size = 10.0f;
	if (positions.size() > particleSystem->getSize()) {
		particleSystem->resize(positions.size(), attr);
	}
	auto& ps = particleSystem->getParticles();
	for (int i = 0; i < positions.size(); ++i) {
		ps[i]->moveTo(positions[i]);
	}

	scene->getPresenter()->updateView();
}
