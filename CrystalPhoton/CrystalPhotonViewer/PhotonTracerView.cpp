#include "PhotonTracerView.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

PhotonTracerView::PhotonTracerView(const std::string& name, World* world, Canvas* canvas) :
	IOkCancelView(name, world, canvas),
	lightView("Light"),
	buildButton("Build")
{
	add(&lightView);
	add(&buildButton);
	buildButton.setFunction([=]() { onBuild(); });

	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>();
	this->particles = new ParticleSystemScene(getWorld()->getNextSceneId(), name, std::move(shape));
	auto presenter = particles->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}

void PhotonTracerView::onBuild()
{
	ParticleAttribute attr;
	attr.color = ColorRGBAf(1, 0, 0, 0);
	attr.size = 10.0f;
	for (int i = 0; i < 10; ++i) {
		particles->getShape()->add(Vector3dd(i, 0, 0), attr);
		particles->getShape()->add(Vector3dd(i, 10, 0), attr);
		particles->getShape()->add(Vector3dd(0, i, 0), attr);
		particles->getShape()->add(Vector3dd(10, i, 0), attr);
	}
	particles->getPresenter()->updateView();
	//tracer.build()
}

void PhotonTracerView::onOk()
{

}
