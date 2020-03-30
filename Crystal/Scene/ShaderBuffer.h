#pragma once

#include "ScreenShaderBuffer.h"
#include "ScreenIdShaderBuffer.h"

namespace Crystal {
	namespace Scene {

class ShaderBuffer
{
public:
	ScreenShaderBuffer screen;
	ScreenIdShaderBuffer parentId;
	ScreenIdShaderBuffer childId;

	/*
	// Model ‚ª•Ï‚í‚Á‚½‚Æ‚«‚¾‚¯”½‰f‚³‚¹‚éD
	void add(ParticleSystemScene* scene);

	void add(WireFrameScene* scene);

	void add(PolygonMeshScene* scene);

	void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	void add(LightScene* scene) { this->lightScenes.push_back(scene); }
	*/
};

	}
}