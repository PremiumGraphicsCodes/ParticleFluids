#include "PolygonMeshEditView.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IView(name),
	polygonMeshView("PolygonMesh"),
	presenterView("Presenter"),
	world(repository),
	idView("Id"),
	nameView("Name"),
	editButton("Edit")
{
	add(&polygonMeshView);
	add(&presenterView);
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
	if (scene == nullptr) {
		return;
	}
	scene->setName(nameView.getValue());

	scene->getPresenter()->removeView(world->getRenderer(), *world->getGLFactory());
	presenterView.setPresenter(scene, world);
}