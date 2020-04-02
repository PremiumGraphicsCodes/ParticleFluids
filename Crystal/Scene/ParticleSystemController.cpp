#include "ParticleSystemController.h"

#include "ParticleSystemScene.h"

using namespace Crystal::Scene;

ParticleSystemController::ParticleSystemController(ParticleSystemScene* model) :
	model(model)
{
}

void ParticleSystemController::createView(PointShader* renderer)
{
	const auto& ps = model->getShape()->getParticles();
	PointBuffer pb;
	for (auto p : ps) {
		pb.add(p->getPosition(), p->getAttribute().color, p->getAttribute().size);
	}
	pb.setMatrix(model->getMatrix());

	auto buffer = std::make_shared<PointShaderScene>();
	buffer->setShader(renderer);
	//buffer->build(glFactory);
	buffer->send(pb);
	view = buffer;
	//pointScenes.push_back(std::move(buffer));
}

void ParticleSystemController::updateView()
{
	//src->get
}

