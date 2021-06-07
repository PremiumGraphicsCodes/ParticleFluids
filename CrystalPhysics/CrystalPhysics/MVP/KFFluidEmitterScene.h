#pragma once

#include "../../../Crystal/Math/Sphere3d.h"

#include "IMVPFluidScene.h"

namespace Crystal {
	namespace Physics {
		//class KFMacroParticle;

class KFFluidEmitterScene : public IMVPFluidScene
{
public:
	KFFluidEmitterScene(const int id, const std::string& name);

	~KFFluidEmitterScene();

	static constexpr auto Type = "KFFluidEmitter";

	Scene::SceneType getType() const { return Type; }

	void emitParticle(const int timeStep);

	void addSource(const Math::Sphere3dd& s) { this->sourcePositions.push_back(s); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	void setInterval(const int interval) { this->interval = interval; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

	void setInitialVelocity(const Math::Vector3df& velocity) { this->initialVelocity = velocity; }

	void clearSources() { this->sourcePositions.clear(); }

private:
	std::vector<Math::Sphere3dd> sourcePositions;
	Math::Vector3df initialVelocity;
	std::pair<int,int> startEndStep;
	int interval;
};

	}
}