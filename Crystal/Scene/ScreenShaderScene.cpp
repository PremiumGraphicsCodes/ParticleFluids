#include "ScreenShaderScene.h"

#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ScreenShaderScene::ScreenShaderScene()
{
}

void ScreenShaderScene::add(ParticleSystemScene* model, GLObjectFactory& glFactory, PointRenderer* shader)
{
	auto scene = new PointShaderScene(model->getName());
	scene->setShader(shader);
	scene->build(glFactory);

	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(model->getMatrix());

	scene->setCamera(camera);
	scene->send(pb);
	this->scenes.push_back(scene);
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