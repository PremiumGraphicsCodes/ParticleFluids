#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"
#include "SmoothShaderScene.h"
#include "MaterialShaderScene.h"
#include "LightShaderScene.h"

#include <list>

namespace Crystal {
	namespace Scene {
		class TextureShaderScene;

class ScreenShaderScene : public IShaderScene
{
public:
	explicit ScreenShaderScene(const std::string& name);

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;
	//std::vector<MaterialShaderScene*> materialScenes;

	void add(PointShaderScene* point);

	void add(LineShaderScene* line);

	void add(SmoothShaderScene* smooth);

	void add(LightShaderScene* light);

	void add(MaterialShaderScene* material);

	void add(TextureShaderScene* texture);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	std::vector<PointShaderScene*> getPointBuffers() const { return pointBuffers; }

	std::vector<LineShaderScene*> getLineBuffers() const { return lineBuffers; }

	std::vector<SmoothShaderScene*> getSmoothBuffers() const { return pmScenes; }

private:
	std::vector<PointShaderScene*> pointBuffers;
	std::vector<LineShaderScene*> lineBuffers;
	std::vector<SmoothShaderScene*> pmScenes;
	std::vector<TextureShaderScene*> textureScenes;
	CameraShaderScene* camera;
};

	}
}