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

	void add(ParticleSystemScene* point, Shader::GLObjectFactory& factory, Shader::PointRenderer* shader);

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