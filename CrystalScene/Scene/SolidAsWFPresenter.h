#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {

class SolidScene;
class LineShaderScene;

class SolidAsWFPresenter : public IPresenter
{
public:
	explicit SolidAsWFPresenter(SolidScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	LineShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	SolidScene* model;
	LineShaderScene* view;
};

	}
}