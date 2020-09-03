#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"
#include "SmoothShaderScene.h"

#include <list>

namespace Crystal {
	namespace Scene {
		class TextureShaderScene;
		class ParticleSystemScene;

class ScreenShaderScene 
{
public:
	ScreenShaderScene();

	void add(IShaderScene* scene);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	std::vector<IShaderScene*> getScenes() const { return scenes; }

private:
	std::vector<IShaderScene*> scenes;
	CameraShaderScene* camera;
};

	}
}