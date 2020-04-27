#include "CameraShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

CameraShaderScene::CameraShaderScene(const std::string& name) :
	IShaderScene(name)
{}

void CameraShaderScene::update(const Camera& camera)
{
	this->projectionMatrix = camera.getProjectionMatrix();
	this->modelViewMatrix = camera.getModelViewMatrix();
	this->eyePosition = camera.getEye();
}
