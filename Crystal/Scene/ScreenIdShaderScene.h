#pragma once

#include "LineShaderScene.h"
#include "TriangleBuffer.h"
#include "TriangleShaderScene.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
		class WireFrameScene;
		class PolygonMeshScene;

class ScreenIdShaderScene
{
public:
	ScreenIdShaderScene();

	void add(PointShaderScene* scene);

	void add(LineShaderScene* scene);

	void add(TriangleShaderScene* scene);

	std::vector<IShaderScene*> getScenes() const { return scenes; }

	void setCamera(CameraShaderScene* camera);

private:
	std::vector<IShaderScene*> scenes;
	CameraShaderScene* camera;
};

	}
}