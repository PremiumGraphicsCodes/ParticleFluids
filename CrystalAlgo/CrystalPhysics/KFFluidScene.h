#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "KFMacroParticle.h"
#include "KFFluidScenePresenter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScenePresenter;

class KFFluidScene : public Scene::IScene
{
public:
	KFFluidScene(const int id, const std::string& name);

	~KFFluidScene();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IPresenter* getPresenter() { return controller.get(); }

	void addParticle(KFMacroParticle* mp) {
		mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<KFMacroParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

	void setPressureCoe(const float coe) { this->pressureCoe = coe; }

	float getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const float coe) { this->viscosityCoe = coe; }

	float getViscosityCoe() const { return this->viscosityCoe; }

private:
	std::list<KFMacroParticle*> particles;
	float pressureCoe;
	float viscosityCoe;
	std::unique_ptr<KFFluidScenePresenter> controller;
};


	}
}
