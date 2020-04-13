#include "LightController.h"

#include "LightScene.h"
#include "LightShaderScene.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

LightController::LightController(LightScene* model) :
	model(model)
{}

void LightController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& l = model->getLight();
	LightShaderScene* mScene = new LightShaderScene();
	mScene->position = l->getPosition();
	mScene->ambient = l->getAmbient();
	mScene->specular = l->getSpecular();
	mScene->diffuse = l->getDiffuse();
	sceneShader->getScene()->screen.lightScenes.push_back(*mScene);
	this->view = mScene;
}

void LightController::updateView()
{
	/*
	const auto& m = model->getMaterial();
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
	*/
}
