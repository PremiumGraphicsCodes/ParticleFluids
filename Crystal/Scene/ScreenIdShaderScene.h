#pragma once

#include "PointShader.h"
#include "LineShader.h"

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

	void add(PolygonMeshScene* scene);

	std::vector<PointShaderScene*> getPointScenes() const { return pointScenes; }

	std::vector<LineShaderScene*> getLineScenes() const { return lineScenes; }

	void setCamera(CameraShaderScene* camera);

private:
	std::vector<PointShaderScene*> pointScenes;
	std::vector<LineShaderScene*> lineScenes;
	std::vector<LineBuffer> triangleIdBuffers;
	CameraShaderScene* camera;
};

	}
}