#include "MaterialController.h"

#include "MaterialScene.h"
#include "MaterialShaderScene.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

MaterialController::MaterialController(MaterialScene* model) :
	model(model)
{}

void MaterialController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& m = model->getMaterial();
	MaterialShaderScene* mScene = new MaterialShaderScene();
	mScene->shininess = m->shininess;
	mScene->ambient = m->ambient;
	mScene->specular = m->specular;
	mScene->diffuse = m->diffuse;
	sceneShader->getBuffer()->screen.materialScenes.push_back(*mScene);
	this->view = mScene;
}

void MaterialController::updateView()
{
	const auto& m = model->getMaterial();
	this->view->shininess = m->shininess;
	this->view->ambient = m->ambient;
	this->view->specular = m->specular;
	this->view->diffuse = m->diffuse;
}
