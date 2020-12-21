#include "PMPresenterView.h"

#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"
#include "../../Crystal/Scene/PMSmoothPresenter.h"
#include "../../Crystal/Scene/PMWirePresenter.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PMPresenterView::PMPresenterView(const std::string& name) :
	ComboBox(name)
{
	add("Smooth");
	add("Wire");

	setSelected("Smooth");

}

void PMPresenterView::setPresenter(PolygonMeshScene* scene, World* world)
{
	const auto name = getSelected();
	if (name == "Smooth") {
		auto presenter = std::make_unique<PMSmoothPresenter>(scene);
		scene->setPresenter(std::move(presenter));
	}
	else if (name == "Wire") {
		auto presenter = std::make_unique<PMWirePresenter>(scene);
		scene->setPresenter(std::move(presenter));
	}

	auto presenter = scene->getPresenter();
	presenter->createView(world->getRenderer(), *world->getGLFactory());
}
