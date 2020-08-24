#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class LightScene;
		class LightShaderScene;

class LightPresenter : public IPresenter
{
public:
	explicit LightPresenter(LightScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	LightScene* model;
	LightShaderScene* view;
};

	}
}