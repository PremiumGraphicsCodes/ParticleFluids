#pragma once

#include "../../Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace VDB {
		class VDBVolume;

class VDBVolumePresenter : public Scene::IPresenter
{
public:
	explicit VDBVolumePresenter(VDBVolume* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBVolume* model;
	Scene::PointShaderScene* view;
};

	}
}