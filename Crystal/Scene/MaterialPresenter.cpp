#include "MaterialPresenter.h"

#include "MaterialScene.h"
#include "MaterialShaderScene.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

MaterialPresenter::MaterialPresenter(MaterialScene* model) :
	model(model),
	view(nullptr)
{}

void MaterialPresenter::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& m = model->getMaterial();
	this->view = new MaterialShaderScene(model->getName());
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
	sceneShader->getScene()->screen.add(this->view);
}

void MaterialPresenter::updateView()
{
	const auto& m = model->getMaterial();
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
}