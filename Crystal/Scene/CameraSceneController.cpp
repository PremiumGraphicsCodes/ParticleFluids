#include "CameraSceneController.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

CameraSceneController::CameraSceneController(CameraScene* model) :
	model(model),
	view(nullptr)
{}

void CameraSceneController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	//sceneShader->getScene()->screen.cameraScene()
}

void CameraSceneController::updateView()
{

}

