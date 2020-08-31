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
	for (auto p : pointBuffers) {
		p->build(glFactory);
	}
	for (auto l : lineBuffers) {
		l->build(glFactory);
	}
	for (auto t : pmScenes) {
		t->build(glFactory);
	}

	return true;
}

void ScreenShaderScene::release(GLObjectFactory& glFactory)
{
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
	for (auto p : pointBuffers) {
		p->render();
	}
	for (auto l : lineBuffers) {
		l->render();
	}
	for (auto t : pmScenes) {
		t->render();
	}
}

void ScreenShaderScene::add(PointShaderScene* point)
{
	point->setCamera(camera);
	this->pointBuffers.push_back(point);
}

void ScreenShaderScene::add(LineShaderScene* line)
{
	line->setCamera(camera);
	this->lineBuffers.push_back(line);
}

void ScreenShaderScene::add(SmoothShaderScene* smooth)
{
	smooth->setCamera(camera);
	this->pmScenes.push_back(smooth);
}

void ScreenShaderScene::add(LightShaderScene* light)
{
}

void ScreenShaderScene::add(MaterialShaderScene* material)
{
}

void ScreenShaderScene::add(TextureShaderScene* texture)
{
	this->textureScenes.push_back(texture);
}