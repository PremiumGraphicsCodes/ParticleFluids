#pragma once

#include "../../Crystal/Scene/IScene.h"

#include "CSPHParticle.h"
//#include "DFFluidSceneController.h"

namespace Crystal {
	namespace Physics {
		//	class KFFluidSceneController;

class CSPHFluidScene : public Scene::IScene
{
public:
	CSPHFluidScene(const int id, const std::string& name);

	~CSPHFluidScene() {}

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() {
		return nullptr;
		//return controller.get();
	}//controller.get(); }

	void addParticle(CSPHParticle* mp) {
		//mp->setScene(this);
		particles.push_back(mp);
	}

	std::list<CSPHParticle*> getParticles() const { return particles; }

	void clearParticles();

	Math::Box3d getBoundingBox() const override;


private:
	std::list<CSPHParticle*> particles;
	//std::unique_ptr<CSPHSceneController> controller;
};

	}
}
