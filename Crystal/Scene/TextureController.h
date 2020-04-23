#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
		class TextureShaderScene;

class TextureController : public IController
{
public:
	explicit TextureController(TextureScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	TextureShaderScene* getView() { return view; }

private:
	TextureScene* model;
	TextureShaderScene* view;
};

	}
}