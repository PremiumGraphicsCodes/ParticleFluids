#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class SceneShader;

class IPresenter
{
public:
	virtual ~IPresenter() {};

	virtual void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory) = 0;

	virtual void updateView() = 0;
};

	}
}