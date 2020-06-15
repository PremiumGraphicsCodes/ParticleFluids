#pragma once

#include "../../Crystal/Scene/IController.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Physics {
		class PBFluidScene;

class PBFluidSceneController : public Scene::IController
{
public:
	explicit PBFluidSceneController(PBFluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	PBFluidScene* model;
	Scene::PointShaderScene* view;
};

	}
}