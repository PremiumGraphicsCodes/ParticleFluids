#include "ParticleSystemController.h"

#include "ParticleSystemScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

ParticleSystemController::ParticleSystemController(ParticleSystemScene* model) :
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr)
{
}

void ParticleSystemController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
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

void ParticleSystemController::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void ParticleSystemController::updateScreenView()
{
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(model->getMatrix());
	this->view->send(pb);
}

void ParticleSystemController::updateParentIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	parentIdBuffer.setMatrix(model->getMatrix());
	for (auto p : particles) {
		DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
	}
	parentIdView->send(parentIdBuffer);
}

void ParticleSystemController::updateChildIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer buffer;
	buffer.setMatrix(model->getMatrix());
	for (auto p : particles) {
		DrawableID childDid(particleId++);
		buffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	childIdView->send(buffer);
}