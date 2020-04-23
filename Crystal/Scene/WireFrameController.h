#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;

class WireFrameController : public IController
{
public:
	explicit WireFrameController(WireFrameScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	LineShaderScene* getView() { return view; }

private:
	WireFrameScene* model;
	LineShaderScene* view;
};

	}
}