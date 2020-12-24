#pragma once

#include "../../Crystal/Scene/IPresenter.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class DFFluidScene;

class DFFluidSceneController : public Scene::IPresenter
{
public:
	explicit DFFluidSceneController(DFFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override{};

	void updateView() override;

private:
	DFFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}