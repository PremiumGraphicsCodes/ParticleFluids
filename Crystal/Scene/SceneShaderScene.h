#pragma once

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneShaderScene
{
public:
	void setCamera(CameraShaderScene* camera);

	void add(ParticleSystemScene* model, Shader::GLObjectFactory& glFactory, Shader::PointRenderer* renderer);

	void add(WireFrameScene* model);

	void add(PolygonMeshScene* model);

	ScreenShaderScene screen;
	ScreenIdShaderScene parentId;
	ScreenIdShaderScene childId;

};

	}
}