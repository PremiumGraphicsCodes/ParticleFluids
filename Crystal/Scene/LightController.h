#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class LightScene;
		class LightShaderScene;

class LightController : public IController
{
public:
	explicit LightController(LightScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	LightScene* model;
	LightShaderScene* view;
};

	}
}