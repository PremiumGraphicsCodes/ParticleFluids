#pragma once

#include "../../Crystal/Scene/IController.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;

class KFFluidSceneController : public Scene::IController
{
public:
	explicit KFFluidSceneController(KFFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	KFFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}