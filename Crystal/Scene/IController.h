#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class SceneShader;

class IController
{
public:
	virtual ~IController() {};

	virtual void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) = 0;

	virtual void updateView() = 0;
};

	}
}