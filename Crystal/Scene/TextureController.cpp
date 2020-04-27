#include "TextureController.h"

#include "SceneShader.h"
#include "TextureScene.h"

using namespace Crystal::Scene;
using namespace Crystal::Shader;

TextureController::TextureController(TextureScene* model) :
	model(model),
	view(nullptr)
{}

void TextureController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	this->view = new TextureShaderScene(model->getName());
	this->view->build(factory);
	this->view->send(*model->getImage());
	sceneShader->getScene()->screen.add(this->view);
}

void TextureController::updateView()
{
	this->view->send(*model->getImage());
}
