#pragma once

#include "IPolygonMeshPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;
		class TriangleShaderScene;

class PolygonMeshPresenter : public IPolygonMeshPresenter
{
public:
	explicit PolygonMeshPresenter(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void removeView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	SmoothShaderScene* getView() { return view; }

private:
	void updateScreenView();

	void updateParentIdView();

	void updateChildIdView();

	SmoothShaderScene* view;
	TriangleShaderScene* parentIdView;
};

	}
}