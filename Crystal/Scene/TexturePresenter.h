#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class TextureScene;
		class TextureShaderScene;

class TexturePresenter : public IPresenter
{
public:
	explicit TexturePresenter(TextureScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	TextureShaderScene* getView() { return view; }

private:
	TextureScene* model;
	TextureShaderScene* view;
};

	}
}