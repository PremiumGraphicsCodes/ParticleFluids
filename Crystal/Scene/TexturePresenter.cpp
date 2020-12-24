#include "TexturePresenter.h"

#include "TextureScene.h"
#include "SceneShader.h"
#include "TextureShaderScene.h"

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
	this->view = sceneShader->getObjectRenderer()->getTextureScene();
	this->index = this->view->getTextures().size();

	auto texture = glFactory.createTextureObject();
	this->view->add(texture);

	updateView();
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
	auto textures = this->view->getTextures();
	textures[index]->send(*model->getImage());
	this->view->update(index);
}

void TexturePresenter::updateParentIdView()
{
}

void TexturePresenter::updateChildIdView()
{
}