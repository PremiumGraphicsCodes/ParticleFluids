#pragma once

#include "../../Crystal/Scene/IController.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/PointShaderScene.h"

namespace Crystal {
	namespace Algo {
		namespace Physics {
			class FluidScene;

class FluidSceneController : public Scene::IController
{
public:
	explicit FluidSceneController(FluidScene* model);

	void createView(Scene::SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	FluidScene* model;
	Scene::PointShaderScene* view;
};

		}
	}
}