#include "ParticleSystemPresenter.h"

#include "ParticleSystemScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

ParticleSystemPresenter::ParticleSystemPresenter(ParticleSystemScene* model) :
	model(model),
	view(nullptr),
	parentIdView(nullptr),
	childIdView(nullptr)
{
}

void ParticleSystemPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		sceneShader->getScene()->screen.add(model, glFactory, sceneShader->getObjectRenderer()->getPointShader());
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

void ParticleSystemPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void ParticleSystemPresenter::updateScreenView()
{
}

void ParticleSystemPresenter::updateParentIdView()
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

void ParticleSystemPresenter::updateChildIdView()
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