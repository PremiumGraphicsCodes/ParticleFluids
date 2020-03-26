#pragma once

#include "PointShaderBuffer.h"
#include "LineShaderBuffer.h"
#include "SmoothShaderBuffer.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class WireFrameScene;
		class PolygonMeshScene;
		class TextureScene;
		class MaterialScene;
		class LightScene;

class ScreenShaderBuffer
{
public:
	void add(ParticleSystemScene* scene);

	void add(WireFrameScene* scene);

	void add(PolygonMeshScene* scene);

	void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	void add(LightScene* scene) { this->lightScenes.push_back(scene); }

	//void build();

	//void release();

	std::vector<PointShaderBuffer> pointBuffers;
	std::vector<LineShaderBuffer> lineBuffers;
	std::vector<SmoothShaderBuffer> pmScenes;
	std::vector<TextureScene*> textureScenes;
	std::vector<MaterialScene*> materialScenes;
	std::vector<LightScene*> lightScenes;
};

	}
}