#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class MaterialScene;
		class SceneShader;

class MaterialController
{
public:
	explicit MaterialController(MaterialScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

private:
	MaterialScene* model;
};
	}
}