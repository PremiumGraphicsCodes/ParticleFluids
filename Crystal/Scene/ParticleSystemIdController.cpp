#include "ParticleSystemIdController.h"

#include "ParticleSystemScene.h"

#include "../Graphics/DrawableId.h"

#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;

ParticleSystemIdController::ParticleSystemIdController(ParticleSystemScene* model) :
	model(model),
	parentView(nullptr)
{
}

void ParticleSystemIdController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{
	const auto objectId = model->getId();
	const auto& particles = model->getShape()->getParticles();
	int particleId = 0;
	parentView = new PointShaderScene(sceneShader->getName());
	//parentView->setMatrix(model->getMatrix());
	PointBuffer parentIdBuffer;
	PointBuffer childIdBuffer;
	childIdBuffer.setMatrix(model->getMatrix());
	for (auto p : particles) {
		DrawableID parentDid(objectId);
		parentIdBuffer.add(p->getPosition(), parentDid.toColor(), p->getAttribute().size);
		//Graphics::DrawableID childDid(particleId++);
		//childIdBuffer.add(p->getPosition(), childDid.toColor(), p->getAttribute().size);
	}
	parentView->send(parentIdBuffer);
	sceneShader->getScene()->parentId.pointIdBuffers.push_back(parentIdBuffer);
}

void ParticleSystemIdController::updateView()
{

}