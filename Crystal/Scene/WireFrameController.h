#pragma once

#include "IController.h"

//#include "LineShaderScene.h"

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

	//LineShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

private:
	WireFrameScene* model;
	LineShaderScene* view;
	LineShaderScene* parentIdView;
};

	}
}