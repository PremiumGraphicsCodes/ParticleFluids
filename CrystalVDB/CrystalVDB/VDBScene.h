#pragma once

#include "CrystalScene/Scene/IScene.h"
#include "VDBVolumeScene.h"
#include "VDBPointsScene.h"
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

	void add(VDBPointsScene* points);

	void add(VDBPolygonMeshScene* mesh);

	Scene::SceneType getType() const override;

	Scene::IPresenter* getPresenter() override;

	std::vector<VDBVolumeScene*> getVolumes() { return volumes; }

	std::vector<VDBPointsScene*> getPoints() { return points; }

	std::vector<VDBPolygonMeshScene*> getMeshes() { return meshes; }

private:
	std::vector<VDBVolumeScene*> volumes;
	std::vector<VDBPointsScene*> points;
	std::vector<VDBPolygonMeshScene*> meshes;
};
	}
}