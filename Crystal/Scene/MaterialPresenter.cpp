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
	const auto buffer = sceneShader->getObjectRenderer()->getMateialBuffer();
	//this->index = buffer->getMaterials().size();
	buffer->add(*this->model->getMaterial());
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
}

void MaterialPresenter::updateParentIdView()
{
}

void MaterialPresenter::updateChildIdView()
{
}