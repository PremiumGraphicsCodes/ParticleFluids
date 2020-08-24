#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "KFMacroParticle.h"
#include "KFFluidSceneController.h"

namespace Crystal {
	namespace Physics {
		class KFFluidSceneController;

class KFFluidScene : public Scene::IScene
{
public:
	KFFluidScene(const int id, const std::string& name);

	~KFFluidScene();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IPresenter* getController() { return controller.get(); }

	void addParticle(KFMacroParticle* mp) {
		mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<KFMacroParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

	void setPressureCoe(const double coe) { this->pressureCoe = coe; }

	double getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const double coe) { this->viscosityCoe = coe; }

	double getViscosityCoe() const { return this->viscosityCoe; }

private:
	std::list<KFMacroParticle*> particles;
	double pressureCoe;
	double viscosityCoe;
	std::unique_ptr<KFFluidSceneController> controller;
};

	}
}
