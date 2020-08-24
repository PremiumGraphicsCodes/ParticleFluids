#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class MaterialScene;
		class SceneShader;
		class MaterialShaderScene;

class MaterialController : public IPresenter
{
public:
	explicit MaterialController(MaterialScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

private:
	MaterialScene* model;
	MaterialShaderScene* view;
};
	}
}