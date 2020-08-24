#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
		class TextureShaderScene;

class TextureController : public IPresenter
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