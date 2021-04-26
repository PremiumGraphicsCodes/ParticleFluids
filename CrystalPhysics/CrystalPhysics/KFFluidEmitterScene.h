#pragma once

#include <vector>
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Sphere3d.h"
#include "../../Crystal/Scene/IParticleSystemScene.h"

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class KFFluidEmitterScene : public Scene::IParticleSystemScene
{
public:
	KFFluidEmitterScene(const int id, const std::string& name);

	~KFFluidEmitterScene();

	static constexpr auto Type = "KFFluidEmitter";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() { return nullptr; }

	void clearParticles();

	void emitParticle();

	Math::Box3d getBoundingBox() const override;

	void addSource(const Math::Sphere3d& s) { this->sourcePositions.push_back(s); }

	void setStartEnd(const int startStep, const int endStep) { this->startEndStep = std::make_pair(startStep, endStep); }

	//std::vector<Math::Vector3df> getPositions() const { return positions; }

	int getStartStep() const { return startEndStep.first; }

	int getEndStep() const { return startEndStep.second; }

	void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	float getPressure() const { return this->pressureCoe; }

	void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	float getViscosityCoe() const { return this->viscosityCoe; }

	void translate(const Math::Vector3dd& v) override { ; }

	void transform(const Math::Matrix3dd& m) override { ; }

	void transform(const Math::Matrix4dd& m) override { ; }

	std::vector<Math::Vector3dd> getPositions() const override;

private:
	std::vector<KFMacroParticle*> particles;
	std::vector<Math::Sphere3d> sourcePositions;
	std::pair<int,int> startEndStep;
	float pressureCoe;
	float viscosityCoe;
};

	}
}