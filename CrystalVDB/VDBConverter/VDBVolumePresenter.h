#pragma once

#include "../../Crystal/Scene/IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
	}
	namespace VDB {
		class VDBVolumeScene;

class VDBVolumePresenter : public Scene::IPresenter
{
public:
	explicit VDBVolumePresenter(VDBVolumeScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	VDBVolumeScene* model;
	Scene::PointShaderScene* view;
};

	}
}