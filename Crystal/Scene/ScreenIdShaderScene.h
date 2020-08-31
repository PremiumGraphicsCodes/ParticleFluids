#pragma once

#include "LineShader.h"
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

	std::vector<PointShaderScene*> getPointScenes() const { return pointScenes; }

	std::vector<LineShaderScene*> getLineScenes() const { return lineScenes; }

	std::vector<TriangleShaderScene*> getTriangleScenes() const { return triangleIdBuffers; }

	void setCamera(CameraShaderScene* camera);

private:
	std::vector<PointShaderScene*> pointScenes;
	std::vector<LineShaderScene*> lineScenes;
	std::vector<TriangleShaderScene*> triangleIdBuffers;
	CameraShaderScene* camera;
};

	}
}