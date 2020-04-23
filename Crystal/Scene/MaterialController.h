#pragma once

#include "IController.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class MaterialScene;
		class SceneShader;
		class MaterialShaderScene;

class MaterialController : public IController
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