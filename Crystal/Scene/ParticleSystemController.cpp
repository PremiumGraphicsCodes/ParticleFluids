#include "ParticleSystemController.h"

#include "ParticleSystemScene.h"
#include "SceneShader.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

ParticleSystemController::ParticleSystemController(ParticleSystemScene* model) :
	model(model),
	view(nullptr)
{
}

void ParticleSystemController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(model->getMatrix());

	view = new PointShaderScene();
	view->setShader(sceneShader->getObjectRenderer()->getPointShader());
	view->build(glFactory);
	view->send(pb);
	sceneShader->getScene()->screen.pointBuffers.push_back(view);
}

void ParticleSystemController::updateView()
{
	//src->get
}

