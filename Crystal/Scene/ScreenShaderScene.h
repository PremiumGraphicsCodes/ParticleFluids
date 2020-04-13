#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"
#include "SmoothShaderScene.h"
#include "MaterialShaderScene.h"

#include <list>

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class WireFrameScene;
		class PolygonMeshScene;
		class TextureScene;
		class MaterialScene;
		class LightScene;

class ScreenShaderScene : public IShaderScene
{
public:
	// Model ‚ª•Ï‚í‚Á‚½‚Æ‚«‚¾‚¯”½‰f‚³‚¹‚éD
	void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	void add(LightScene* scene) { this->lightScenes.push_back(scene); }

	bool build(Shader::GLObjectFactory& glFactory) override;

	void release(Shader::GLObjectFactory& glFactory) override;

	void render() override;

	std::vector<PointShaderScene> pointBuffers;
	std::vector<LineShaderScene> lineBuffers;
	std::vector<SmoothShaderScene> pmScenes;
	std::vector<TextureScene*> textureScenes;
	std::vector<MaterialShaderScene> materialScenes;
	std::vector<LightScene*> lightScenes;
};

	}
}