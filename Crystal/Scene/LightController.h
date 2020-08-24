#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class LightScene;
		class LightShaderScene;

class LightController : public IPresenter
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