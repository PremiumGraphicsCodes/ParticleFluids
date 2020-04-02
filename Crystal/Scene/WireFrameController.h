#pragma once

namespace Crystal {
	namespace Scene {
		class WireFrameScene;
		class LineShaderScene;
		class LineShader;

class WireFrameController
{
public:
	explicit WireFrameController(WireFrameScene* model);

	void createView(LineShader* renderer);

	void updateView();

private:
	WireFrameScene* model;
	LineShaderScene* view;
};

	}
}