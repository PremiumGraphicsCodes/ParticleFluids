#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class LineShaderScene;

class PMToWFPresenter : public IPresenter
{
public:
	explicit PMToWFPresenter(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	LineShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	PolygonMeshScene* model;
	LineShaderScene* view;
};

	}
}