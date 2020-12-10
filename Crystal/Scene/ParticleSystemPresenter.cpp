#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"
#include "SceneShader.h"
#include "PointShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

ParticleSystemPresenter::ParticleSystemPresenter(ParticleSystemScene* model) :
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr),
	doBlend(false)
{
}

void ParticleSystemPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new PointShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->view->build(glFactory);
		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	{
		this->parentIdView = new PointShaderScene(model->getName());
		this->parentIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->parentIdView->build(glFactory);
		sceneShader->getParentIdRenderer()->addScene(this->parentIdView);
	}

	{
		this->childIdView = new PointShaderScene(model->getName());
		this->childIdView->setShader(sceneShader->getObjectRenderer()->getPointShader());
		this->childIdView->build(glFactory);
		sceneShader->getChildIdRenderer()->addScene(this->childIdView);
	}
	updateView();
}

void ParticleSystemPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void ParticleSystemPresenter::updateScreenView()
{
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}

	this->view->setBlend(this->doBlend);
	this->view->send(pb);
	this->view->setVisible(model->isVisible());
}

void ParticleSystemPresenter::updateParentIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer parentIdBuffer;
	for (auto p : particles) {
		DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
	}
	parentIdView->send(parentIdBuffer);
	parentIdView->setVisible(model->isVisible());
}

void ParticleSystemPresenter::updateChildIdView()
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	PointBuffer buffer;
	for (auto p : particles) {
		DrawableID childDid(particleId++);
		buffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	childIdView->send(buffer);
	childIdView->setVisible(model->isVisible());
}