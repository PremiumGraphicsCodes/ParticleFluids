#include "CameraPresenter.h"

#include "SceneShader.h"

#include "CameraScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

CameraPresenter::CameraPresenter(CameraScene* model) :
	model(model),
	view(nullptr)
{}

void CameraPresenter::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto& m = model->getCamera();
	this->view = new CameraShaderScene(model->getName());
	this->view->update(*m);
	sceneShader->getScene()->setCamera(this->view);

	//sceneShader->getScene()->screen.cameraScene()
}

void CameraPresenter::updateView()
{
	const auto m = model->getCamera();
	this->view->update(*m);
}
