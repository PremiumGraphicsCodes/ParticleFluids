#include "VolumeController.h"

#include "VolumeScene.h"
#include "SceneShader.h"
#include "PointShaderScene.h"
#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Scene;
using namespace Crystal::Shader;

VolumeController::VolumeController(VolumeScene* model) :
	model(model)
{}

void VolumeController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getScene()->screen.add(this->view);
	}

	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->parentIdView->build(glFactory);
		sceneShader->getScene()->parentId.add(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->childIdView->build(glFactory);
		sceneShader->getScene()->childId.add(this->childIdView);
	}
	updateView();
}

void VolumeController::updateView()
{

}

void VolumeController::updateScreenView()
{
	/*
	model->getShape()->
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(model->getMatrix());
	this->view->send(pb);
	*/
}