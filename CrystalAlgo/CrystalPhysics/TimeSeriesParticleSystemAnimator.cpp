#include "TimeSeriesParticleSystemAnimator.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Physics;


TimeSeriesParticleSystemAnimator::TimeSeriesParticleSystemAnimator(ParticleSystemScene* particleSystem, TimeSeriesParticleSystemReader* reader) :
	particleSystem(particleSystem),
	reader(reader)
{}

void TimeSeriesParticleSystemAnimator::step()
{
	const auto positions = reader->getPositions();

	auto& ps = particleSystem->getShape()->getParticles();
	for (int i = 0; i < positions.size(); ++i) {
		ps[i]->moveTo(positions[i]);
	}
}
