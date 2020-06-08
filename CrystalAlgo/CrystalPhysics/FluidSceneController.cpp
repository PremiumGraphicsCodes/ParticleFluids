#include "FluidSceneController.h"

#include "FluidScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Algo::Physics;

FluidSceneController::FluidSceneController(FluidScene* model) :
	model(model),
	view(nullptr)
{}

void FluidSceneController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getScene()->screen.add(this->view);
	}
	updateView();
}

void FluidSceneController::updateView()
{
	const auto& ps = model->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), glm::vec4(1,1,1,1), 10.0);
	}
	pb.setMatrix(Math::Matrix4dd());
	this->view->send(pb);

}