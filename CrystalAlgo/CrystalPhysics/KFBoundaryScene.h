#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "KFBoundaryParticle.h"
#include "KFFluidScenePresenter.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScenePresenter;

class KFBoundaryScene : public Scene::IScene
{
public:
	KFBoundaryScene(const int id, const std::string& name);

	~KFBoundaryScene();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IPresenter* getPresenter() {
		return nullptr;
	}//controller.get(); }

	void addParticle(KFBoundaryParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<KFBoundaryParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

	void setPressureCoe(const double coe) { this->pressureCoe = coe; }

	double getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const double coe) { this->viscosityCoe = coe; }

	double getViscosityCoe() const { return this->viscosityCoe; }

private:
	std::list<KFBoundaryParticle*> particles;
	double pressureCoe;
	double viscosityCoe;
	//std::unique_ptr<KFFluidScenePresenter> controller;
};

	}
}
