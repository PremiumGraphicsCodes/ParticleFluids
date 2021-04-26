#include "KFFluidEmitterScene.h"

#include "KFMacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

KFFluidEmitterScene::KFFluidEmitterScene(const int id, const std::string& name) :
	IKFFluidScene(id, name)
{
}

KFFluidEmitterScene::~KFFluidEmitterScene()
{
	clearParticles();
}

void KFFluidEmitterScene::emitParticle()
{
	for (const auto& s : sourcePositions) {
		auto mp = new KFMacroParticle(s.getRadius(), s.getCenter());
		addParticle(mp);
	}
}