#include "IVolAddView.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::UI;

IVolAddView::IVolAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "Volume01"),
	presenterView("Presenter"),
	colorMapView("ColorMap")
{
	add(&nameView);
	add(&presenterView);
	add(&colorMapView);
}

void IVolAddView::addVolume(const Shape::Volume<float>& volume)
{
	/*
	auto attr = attributeView.getValue();
	auto name = nameView.getValue();
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	auto scene = new ParticleSystemScene(getWorld()->getNextSceneId(), name, std::move(shape));
	getWorld()->getScenes()->addScene(scene);
	const auto newId = scene->getId();

	auto presenter = scene->getPresenter();
	presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	*/
}
