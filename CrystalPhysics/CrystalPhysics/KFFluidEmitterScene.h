#pragma once

#include "../../Crystal/Math/Sphere3d.h"

#include "IKFFluidScene.h"

namespace Crystal {
	namespace Physics {
		//class KFMacroParticle;

class KFFluidEmitterScene : public IKFFluidScene
{
public:
	KFFluidEmitterScene(const int id, const std::string& name);

	~KFFluidEmitterScene();

	static constexpr auto Type = "KFFluidEmitter";

	Scene::SceneType getType() const { return Type; }

	void emitParticle(const int timeStep);

	void addSource(const Math::Sphere3d& s) { this->sourcePositions.push_back(s); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	void setInterval(const int interval) { this->interval = interval; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

	void clearSources() { this->sourcePositions.clear(); }

private:
	std::vector<Math::Sphere3d> sourcePositions;
	std::pair<int,int> startEndStep;
	int interval;
};

	}
}