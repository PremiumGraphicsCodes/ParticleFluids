#pragma once

#include "LineShaderScene.h"
#include "TriangleBuffer.h"
#include "TriangleShaderScene.h"

namespace Crystal {
	namespace Scene {
		class PointShaderScene;
		class WireFrameScene;
		class PolygonMeshScene;

class ScreenIdShaderScene : public IShaderScene
{
public:
	explicit ScreenIdShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) { return true; }

	void release(Shader::GLObjectFactory& glFactory) {}

	void render() override;

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