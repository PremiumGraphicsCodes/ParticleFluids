#pragma once

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;
		class LineShader;

class WireFrameController
{
public:
	explicit WireFrameController(WireFrameScene* model);

	void createView(LineShader* renderer, Shader::GLObjectFactory& factory);

	void updateView();

private:
	WireFrameScene* model;
	LineShaderScene* view;
};

	}
}