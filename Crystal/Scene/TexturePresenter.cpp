#include "TexturePresenter.h"

#include "SceneShader.h"
#include "TextureScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Shader;

TexturePresenter::TexturePresenter(TextureScene* model) :
	model(model),
	view(nullptr)
{}

void TexturePresenter::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view = new TextureShaderScene(model->getName());
	this->view->build(factory);
	this->view->send(*model->getImage());
	sceneShader->getScene()->screen.add(this->view);
}

void TexturePresenter::updateView()
{
	this->view->send(*model->getImage());
}
