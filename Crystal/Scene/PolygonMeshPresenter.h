#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;

class PolygonMeshPresenter : public IPresenter
{
public:
	explicit PolygonMeshPresenter(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();


	PolygonMeshScene* model;
	SmoothShaderScene* view;
};

	}
}