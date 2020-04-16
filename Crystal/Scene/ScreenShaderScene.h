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
	explicit ScreenShaderScene(const std::string& name) :
		IShaderScene(name)
	{}

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	std::vector<LineShaderScene*> lineBuffers;
	std::vector<SmoothShaderScene*> pmScenes;
	std::vector<TextureShaderScene*> textureScenes;
	std::vector<MaterialShaderScene*> materialScenes;
	std::vector<LightShaderScene*> lightScenes;

	void add(PointShaderScene* point) {
		this->pointBuffers.push_back(point);
		addChild(point);
	}

	std::vector<PointShaderScene*> getPointBuffers() const { return pointBuffers; }

private:
	std::vector<PointShaderScene*> pointBuffers;

};

	}
}