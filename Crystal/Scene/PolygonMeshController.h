#pragma once

#include "IController.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;

class PolygonMeshController : public IController
{
public:
	explicit PolygonMeshController(PolygonMeshScene* model);

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