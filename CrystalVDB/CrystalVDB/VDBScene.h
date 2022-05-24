#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "VDBVolumeScene.h"
#include "VDBParticleSystemScene.h"

namespace Crystal {
	namespace VDB {

class VDBScene : public Scene::IScene
{
public:
	VDBScene(const int id, const std::string& name) :
		Scene::IScene(id, name)
	{}

	void add(VDBVolumeScene* volume);

	void add(VDBParticleSystemScene* points);

	Scene::SceneType getType() const override;

	Scene::IPresenter* getPresenter() override;

private:
	std::vector<VDBVolumeScene*> volumes;
	std::vector<VDBParticleSystemScene*> points;
};
	}
}