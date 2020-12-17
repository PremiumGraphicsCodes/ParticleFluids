#include "PolygonMeshEditView.h"

#include "../../Crystal/Scene/PMAsWFPresenter.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IView(name),
	polygonMeshView("PolygonMesh"),
	world(repository),
	idView("Id"),
	nameView("Name"),
	editButton("Edit")
{
	add(&polygonMeshView);
	add(&idView);
	add(&nameView);
	add(&editButton);
	editButton.setFunction([=]() { onEdit(); });
}

void PolygonMeshEditView::setValue(PolygonMeshScene* value)
{
	polygonMeshView.setValue(value->getShape());
	idView.setValue(value->getId());
	nameView.setValue(value->getName());
}

void PolygonMeshEditView::onEdit()
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(idView.getValue());
	scene->setName(nameView.getValue());

	/*
	scene->getPresenter()->removeView(world->getRenderer(), *world->getGLFactory());

	const auto presenterName = this->polygonMeshView.getPresenterName();
	if (presenterName == "Smooth") {
		auto presenter = std::make_unique<PolygonMeshPresenter>(scene);
		scene->setPresenter(std::move(presenter));
	}
	else if (presenterName == "Wire") {
		auto presenter = std::make_unique<PMAsWFPresenter>(scene);
		scene->setPresenter(std::move(presenter));
	}
	scene->getPresenter()->createView(world->getRenderer(), *world->getGLFactory());
	*/
}