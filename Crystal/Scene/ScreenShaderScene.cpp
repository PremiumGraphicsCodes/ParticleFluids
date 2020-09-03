#include "ScreenShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenShaderScene::ScreenShaderScene(const std::string& name) :
	IShaderScene(name)
{}

bool ScreenShaderScene::build(GLObjectFactory& glFactory)
{
	return true;
}

void ScreenShaderScene::release(GLObjectFactory& glFactory)
{
}

void ScreenShaderScene::render()
{
}

void ScreenShaderScene::add(PointShaderScene* point)
{
	point->setCamera(camera);
	this->scenes.push_back(point);
}

void ScreenShaderScene::add(LineShaderScene* line)
{
	line->setCamera(camera);
	this->scenes.push_back(line);
}

void ScreenShaderScene::add(SmoothShaderScene* smooth)
{
	smooth->setCamera(camera);
	this->scenes.push_back(smooth);
}

void ScreenShaderScene::add(LightShaderScene* light)
{
}

void ScreenShaderScene::add(MaterialShaderScene* material)
{
}