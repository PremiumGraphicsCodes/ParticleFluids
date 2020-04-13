#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class LightScene;
		class SceneShader;
		class LightShaderScene;

class LightController
{
public:
	explicit LightController(LightScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

private:
	LightScene* model;
	LightShaderScene* view;
};

	}
}