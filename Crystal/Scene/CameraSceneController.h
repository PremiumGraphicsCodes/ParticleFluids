#pragma once

namespace Crystal {
	namespace Scene {
		class CameraScene;
		class CameraShaderScene;

class CameraSceneController
{
public:
	explicit CameraSceneController(CameraScene* model);

	//void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	//PointShaderScene* getView() { return view; }

private:
	CameraShaderScene* view;
};

	}
}