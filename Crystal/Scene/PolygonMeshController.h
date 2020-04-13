#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;
		class SceneShader;

class PolygonMeshController
{
public:
	explicit PolygonMeshController(PolygonMeshScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	SmoothShaderScene* getView() { return view; }

private:
	PolygonMeshScene* model;
	SmoothShaderScene* view;
};

	}
}