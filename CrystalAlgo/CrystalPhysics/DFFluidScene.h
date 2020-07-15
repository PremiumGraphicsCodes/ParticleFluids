#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "DFSPHParticle.h"
//#include "KFFluidSceneController.h"

namespace Crystal {
	namespace Physics {
	//	class KFFluidSceneController;

class DFFluidScene : public Scene::IScene
{
public:
	DFFluidScene(const int id, const std::string& name);

	~DFFluidScene();

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() {
		return nullptr;
	}//controller.get(); }

	void addParticle(DFSPHParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<DFSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;

	void setPressureCoe(const double coe) { this->pressureCoe = coe; }

	double getPressureCoe() const { return this->pressureCoe; }

	void setViscosityCoe(const double coe) { this->viscosityCoe = coe; }

	double getViscosityCoe() const { return this->viscosityCoe; }

private:
	std::list<DFSPHParticle*> particles;
	double pressureCoe;
	double viscosityCoe;
	//std::unique_ptr<KFFluidSceneController> controller;
};

	}
}
