#include "KFFluidEmitterScene.h"

#include "MVPVolumeParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFFluidEmitterScene::KFFluidEmitterScene(const int id, const std::string& name) :
	IKFFluidScene(id, name),
	interval(10)
{
}

KFFluidEmitterScene::~KFFluidEmitterScene()
{
	clearParticles();
}

void KFFluidEmitterScene::emitParticle(const int timeStep)
{
	const auto start = getStartStep();
	const auto end = getEndStep();
	if (start <= timeStep && timeStep <= end) {
		const auto elapsed = timeStep - start;
		if (elapsed % interval == 0) {
			for (const auto& s : sourcePositions) {
				auto mp = new MVPVolumeParticle(s.getRadius(), s.getCenter());
				mp->distributePoints(3, 3, 3, 1.0f);
				mp->setVelocity(this->initialVelocity);
				addParticle(mp);
			}
		}
	}
}