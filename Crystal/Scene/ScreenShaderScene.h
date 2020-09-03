#pragma once

#include "PointShaderScene.h"
#include "LineShaderScene.h"
#include "SmoothShaderScene.h"

#include <list>

namespace Crystal {
	namespace Scene {
		class TextureShaderScene;

class ScreenShaderScene 
{
public:
	ScreenShaderScene();

	void add(PointShaderScene* point);

	void add(LineShaderScene* line);

	void add(SmoothShaderScene* smooth);

	void setCamera(CameraShaderScene* camera) { this->camera = camera; }

	std::vector<IShaderScene*> getScenes() const { return scenes; }

private:
	std::vector<IShaderScene*> scenes;
	CameraShaderScene* camera;
};

	}
}