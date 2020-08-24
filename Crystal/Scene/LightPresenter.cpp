#include "LightPresenter.h"

#include "LightScene.h"
#include "LightShaderScene.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

LightPresenter::LightPresenter(LightScene* model) :
	model(model),
	view(nullptr)
{}

void LightPresenter::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& l = model->getLight();
	this->view = new LightShaderScene(model->getName());
	this->view->position = l->getPosition();
	this->view->ambient = l->getAmbient();
	this->view->specular = l->getSpecular();
	this->view->diffuse = l->getDiffuse();
	sceneShader->getScene()->screen.add(this->view);
}

void LightPresenter::updateView()
{
	const auto& l = model->getLight();
	this->view->position = l->getPosition();
	this->view->ambient = l->getAmbient();
	this->view->specular = l->getSpecular();
	this->view->diffuse = l->getDiffuse();
}
