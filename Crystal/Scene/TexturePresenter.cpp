#include "TexturePresenter.h"

#include "TextureScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

TexturePresenter::TexturePresenter(TextureScene* model) :
	model(model),
	view(nullptr),
	index(0)
{
}

void TexturePresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	/*
	this->view = sceneShader->getObjectRenderer()->getMateialBuffer();
	this->index = this->view->getMaterials().size();
	this->view->add(*this->model->getMaterial());
	*/
}

void TexturePresenter::removeView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	/*
	this->view->release(factory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
	*/
}

void TexturePresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void TexturePresenter::updateScreenView()
{
	//this->view->update(index);
}

void TexturePresenter::updateParentIdView()
{
}

void TexturePresenter::updateChildIdView()
{
}