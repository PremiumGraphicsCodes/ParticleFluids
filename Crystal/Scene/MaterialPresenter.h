#pragma once

#include "IPolygonMeshPresenter.h"

namespace Crystal {
	namespace Scene {
		class MaterialScene;
		class MaterialShaderScene;

class MaterialPresenter : public IPresenter
{
public:
	explicit MaterialPresenter(MaterialScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	//SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	MaterialScene* model;
	MaterialShaderScene* view;
	int index = 0;
};

	}
}