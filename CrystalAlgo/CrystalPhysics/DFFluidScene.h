#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "DFSPHParticle.h"
#include "DFFluidSceneController.h"

namespace Crystal {
	namespace Physics {
	//	class KFFluidSceneController;

class DFFluidScene : public Scene::IScene
{
public:
	DFFluidScene(const int id, const std::string& name);

	~DFFluidScene() {}

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() {
		return controller.get();
	}//controller.get(); }

	void addParticle(DFSPHParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<DFSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;


private:
	std::list<DFSPHParticle*> particles;
	std::unique_ptr<DFFluidSceneController> controller;
};

	}
}
