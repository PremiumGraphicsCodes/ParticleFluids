#pragma once

#include "../../Crystal/Scene/IScene.h"

//#include "MacroParticle.h"
#include "PBFluidSceneController.h"
#include "SPHKernel.h"

namespace Crystal {
	namespace Physics {
		class PBSPHParticle;

class PBFluidScene : public Scene::IScene
{
public:
	PBFluidScene(const int id, const std::string& name);

	~PBFluidScene();

	void clearParticles();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IPresenter* getPresenter() { return controller.get(); }

	void addParticle(PBSPHParticle* mp) { particles.push_back(mp); }

	std::list<PBSPHParticle*> getParticles() const { return particles; }

	Math::Box3d getBoundingBox() const override;

	SPHKernel* getKernel() { return &kernel; }

	float getRestDensity() const { return restDensity; }

	void setEffectLength(const float effectLength);

	void setRestDensity(const float restDensity);

	void setStiffness(const float s) { this->stiffness = s; }

	float getStiffness() const { return stiffness; }

	void setVicsosity(const float v) { this->viscosity = v; }

	float getViscosity() const { return viscosity; }

	bool isBoundary() const { return _isBoundary; }

	void setIsBoundary(const bool b) { _isBoundary = b; }

private:
	std::list<PBSPHParticle*> particles;
	std::unique_ptr<PBFluidSceneController> controller;
	SPHKernel kernel;
	float restDensity;
	float stiffness;
	float viscosity;
	bool _isBoundary;
};

	}
}