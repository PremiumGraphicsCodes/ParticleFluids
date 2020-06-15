#pragma once

#include "../../Crystal/Scene/IScene.h"

//#include "MacroParticle.h"
#include "PBFluidSceneController.h"

namespace Crystal {
		namespace Physics {
			class PBSPHParticle;

class PBFluidScene : public Scene::IScene
{
public:
	PBFluidScene(const int id, const std::string& name);

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Scene::IController* getController() { return controller.get(); }

	void addParticle(PBSPHParticle* mp) { particles.push_back(mp); }

	std::list<PBSPHParticle*> getParticles() const { return particles; }

private:
	std::list<PBSPHParticle*> particles;
	std::unique_ptr<PBFluidSceneController> controller;
};

	}
}
