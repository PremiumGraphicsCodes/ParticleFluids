#pragma once

#include "IPresenter.h"

//#include "LineShaderScene.h"

namespace Crystal {
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;

class WireFramePresenter : public IPresenter
{
public:
	explicit WireFramePresenter(WireFrameScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

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