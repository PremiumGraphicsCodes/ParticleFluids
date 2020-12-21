#include "MaterialPresenter.h"

#include "MaterialScene.h"
#include "SceneShader.h"
//#include "PointShaderScene.h"
#include "SmoothShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

MaterialPresenter::MaterialPresenter(MaterialScene* model) :
	model(model)
{
}

void MaterialPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	this->view = sceneShader->getObjectRenderer()->getMateialBuffer();
	this->index = this->view->getMaterials().size();
	this->view->add(*this->model->getMaterial());
}

void MaterialPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void MaterialPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void MaterialPresenter::updateScreenView()
{
	this->view->update(index);
}

void MaterialPresenter::updateParentIdView()
{
}

void MaterialPresenter::updateChildIdView()
{
}