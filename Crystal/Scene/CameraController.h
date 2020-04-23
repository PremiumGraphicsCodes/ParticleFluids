#pragma once

#include "IController.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class CameraScene;
		class CameraShaderScene;
		class SceneShader;

class CameraController : public IController
{
public:
	explicit CameraController(CameraScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) override;

	void updateView() override;

	CameraShaderScene* getView() { return view; }

private:
	CameraScene* model;
	CameraShaderScene* view;
};

	}
}