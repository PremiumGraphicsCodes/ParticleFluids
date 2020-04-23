#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class CameraScene;
		class CameraShaderScene;
		class SceneShader;

class CameraController
{
public:
	explicit CameraController(CameraScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	CameraShaderScene* getView() { return view; }

private:
	CameraScene* model;
	CameraShaderScene* view;
};

	}
}