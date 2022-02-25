#pragma once

#include "CrystalScene/Scene/IScene.h"

#include "MPSParticle.h"
//#include "IISPHFluidSceneController.h"

namespace Crystal {
	namespace Physics {

class MPSFluidScene : public Scene::IScene
{
public:
	MPSFluidScene(const int id, const std::string& name);

	~MPSFluidScene() {}

	static constexpr auto Type = "MPSFluid";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter() {
		return nullptr;
	}//return controller.get(); }//controller.get(); }

	void addParticle(MPSParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<MPSParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3dd getBoundingBox() const override;


private:
	std::list<MPSParticle*> particles;
	//std::unique_ptr<IISPHFluidSceneController> controller;
};

	}
}
