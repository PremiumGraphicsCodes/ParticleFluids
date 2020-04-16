#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class TextureScene;
		class SceneShader;
		class TextureShaderScene;

class TextureController
{
public:
	explicit TextureController(TextureScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

private:
	TextureScene* model;
	TextureShaderScene* view;
};

	}
}