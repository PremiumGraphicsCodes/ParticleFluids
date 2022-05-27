#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "VDBVolumeScene.h"
#include "VDBParticleSystemScene.h"
#include "VDBPolygonMeshScene.h"

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

	void add(VDBPolygonMeshScene* mesh);

	Scene::SceneType getType() const override;

	Scene::IPresenter* getPresenter() override;

	std::vector<VDBVolumeScene*> getVolumes() { return volumes; }

	std::vector<VDBParticleSystemScene*> getPoints() { return points; }

	std::vector<VDBPolygonMeshScene*> getMeshes() { return meshes; }

private:
	std::vector<VDBVolumeScene*> volumes;
	std::vector<VDBParticleSystemScene*> points;
	std::vector<VDBPolygonMeshScene*> meshes;
};
	}
}