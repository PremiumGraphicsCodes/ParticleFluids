#include "LightPresenter.h"

#include "MaterialScene.h"
#include "SceneShader.h"

#include "LightScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

LightPresenter::LightPresenter(LightScene* model) :
	model(model),
	view(nullptr),
	index(0)
{
}

void LightPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	this->view = sceneShader->getObjectRenderer()->getLightScene();
	this->index = this->view->getMaterials().size();
	this->view->add(*this->model->getLight());
}

void LightPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void LightPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void LightPresenter::updateScreenView()
{
	this->view->update(index);
}

void LightPresenter::updateParentIdView()
{
}

void LightPresenter::updateChildIdView()
{
}