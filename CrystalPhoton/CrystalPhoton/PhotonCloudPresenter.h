#pragma once

#include "../../CrystalScene/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace Photon {
		class PhotonCloudScene;

class PhotonCloudPresenter : public Scene::IPresenter
{
public:
	explicit PhotonCloudPresenter(PhotonCloudScene* model);

	void createView(Scene::SceneShader* sceneShader) override;

	void removeView(Scene::SceneShader* sceneShader) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	PhotonCloudScene* model;
	Scene::PointShaderScene* view;
};

	}
}