#pragma once

#include "../../Crystal/Scene/IController.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class CSPHFluidScene;

class CSPHFluidSceneController : public Scene::IPresenter
{
public:
	explicit CSPHFluidSceneController(CSPHFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	CSPHFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}