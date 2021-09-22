#pragma once

#include "CrystalScene/Scene/IPresenter.h"

#include "CrystalScene/Scene/SceneShader.h"
#include "CrystalScene/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class CSPHFluidScene;

class CSPHFluidSceneController : public Scene::IPresenter
{
public:
	explicit CSPHFluidSceneController(CSPHFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) {};

	void updateView() override;

private:
	CSPHFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}