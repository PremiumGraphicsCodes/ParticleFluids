#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;
		class LineShader;
		class SceneShader;

class WireFrameController
{
public:
	explicit WireFrameController(WireFrameScene* model);

	void createView(SceneShader* sceneShader, Shader::GLObjectFactory& factory);

	void updateView();

	LineShaderScene* getView() { return view; }

private:
	WireFrameScene* model;
	LineShaderScene* view;
};

	}
}