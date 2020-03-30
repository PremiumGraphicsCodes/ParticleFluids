#pragma once

#include "ScreenShaderScene.h"
#include "ScreenIdShaderBuffer.h"

namespace Crystal {
	namespace Scene {

class ShaderBuffer
{
public:
	ScreenShaderScene screen;
	ScreenIdShaderBuffer parentId;
	ScreenIdShaderBuffer childId;

	// Model ‚ª•Ï‚í‚Á‚½‚Æ‚«‚¾‚¯”½‰f‚³‚¹‚éD
	void add(ParticleSystemScene* scene) {
		screen.add(scene);
	}

	void add(WireFrameScene* scene) {
		screen.add(scene);
	}

	void add(PolygonMeshScene* scene) {
		screen.add(scene);
	}

	//void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	//void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	//void add(LightScene* scene) { this->lightScenes.push_back(scene); }
};

	}
}