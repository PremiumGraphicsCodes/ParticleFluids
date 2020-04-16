#include "MaterialController.h"

#include "MaterialScene.h"
#include "MaterialShaderScene.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

MaterialController::MaterialController(MaterialScene* model) :
	model(model),
	view(nullptr)
{}

void MaterialController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& m = model->getMaterial();
	this->view = new MaterialShaderScene();
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
	sceneShader->getScene()->screen.materialScenes.push_back(this->view);
}

void MaterialController::updateView()
{
	const auto& m = model->getMaterial();
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
}
