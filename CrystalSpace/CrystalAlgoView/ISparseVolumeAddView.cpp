#include "ISparseVolumeAddView.h"

#include "../CrystalAlgo/SparseVolumeScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Space;

ISparseVolumeAddView::ISparseVolumeAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	nameView("Name", "SparseVolume01"),
	presenterView("Presenter"),
	colorMapView("ColorMap")
{
	add(&nameView);
	add(&presenterView);
	add(&colorMapView);
}

void ISparseVolumeAddView::addVolume(std::unique_ptr<Volume<float>> volume)
{
	/*
	auto scene = new SparseVolumeScene(getWorld()->getNextSceneId(), nameView.getValue()); std::move(volume));
	getWorld()->getScenes()->addScene(scene);

	scene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	*/
}
