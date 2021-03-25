#include "IVolAddView.h"

#include "../../Crystal/Shape/Volume.h"
#include "../../Crystal/Scene/VolumeScene.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Shape;
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

void IVolAddView::addVolume(std::unique_ptr<Volume<float>> volume)
{
	auto scene = new VolumeScene(getWorld()->getNextSceneId(), nameView.getValue(), std::move(volume));
	getWorld()->getScenes()->addScene(scene);

	scene->getPresenter()->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
}
