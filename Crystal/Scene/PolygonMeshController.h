#pragma once

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;
		class SmoothShaderScene;
		class LineShader;

class PolygonMeshController
{
public:
	explicit PolygonMeshController(WireFrameScene* model);

	void createView(LineShader* renderer);

	void updateView();

private:
	PolygonMeshScene* model;
	LineShaderScene* view;
};

	}
}