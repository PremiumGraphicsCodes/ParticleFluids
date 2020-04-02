#pragma once

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneShaderScene
{
public:
	ScreenShaderScene screen;
	ScreenIdShaderScene parentId;
	ScreenIdShaderScene childId;

	// Model ‚ª•Ï‚í‚Á‚½‚Æ‚«‚¾‚¯”½‰f‚³‚¹‚éD
	void add(WireFrameScene* scene, Shader::GLObjectFactory& glFactory) {
		screen.add(scene, glFactory);
	}

	void add(PolygonMeshScene* scene, Shader::GLObjectFactory& glFactory) {
		screen.add(scene, glFactory);
	}

	//void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	//void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	//void add(LightScene* scene) { this->lightScenes.push_back(scene); }
};

	}
}