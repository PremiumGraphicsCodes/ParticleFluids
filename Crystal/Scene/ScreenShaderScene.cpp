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
	const auto& children = getChildren();
	for (auto c : children) {
		c->build(glFactory);
	}

	return true;
}

void ScreenShaderScene::release(GLObjectFactory& glFactory)
{
	const auto& children = getChildren();
	for (auto c : children) {
		c->release(glFactory);
	}

	for (auto& lb : lineBuffers) {
		lb->release(glFactory);
	}
	lineBuffers.clear();
	for (auto& pm : pmScenes) {
		pm->release(glFactory);
	}
	pmScenes.clear();

	textureScenes.clear();
	//materialScenes.clear();
	//lightScenes.clear();
}

void ScreenShaderScene::render()
{
	const auto& children = getChildren();
	for (auto c : children) {
		c->render();
	}
}

void ScreenShaderScene::add(PointShaderScene* point)
{
	this->pointBuffers.push_back(point);
	addChild(point);
}

void ScreenShaderScene::add(LineShaderScene* line)
{
	this->lineBuffers.push_back(line);
	addChild(line);
}

void ScreenShaderScene::add(SmoothShaderScene* smooth)
{
	this->pmScenes.push_back(smooth);
	addChild(smooth);
}

void ScreenShaderScene::add(LightShaderScene* light)
{
	//this->lineBuffers.push_back(light);
	addChild(light);
}

void ScreenShaderScene::add(MaterialShaderScene* material)
{
	addChild(material);
}