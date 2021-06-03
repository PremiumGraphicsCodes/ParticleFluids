#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class SPHFlameScene;

class SPHFlameSceneController : public Scene::IPresenter
{
public:
	explicit SPHFlameSceneController(SPHFlameScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) {};

	void updateView() override;

private:
	SPHFlameScene* model;
	Scene::PointShaderScene* view;
};

	}
}