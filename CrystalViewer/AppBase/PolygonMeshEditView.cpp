#include "PolygonMeshEditView.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IView(name),
	polygonMeshView("PolygonMesh"),
	world(repository),
	idView("Id"),
	nameView("Name"),
	editButton("Edit"),
	presenterView("Presenter")
{
	add(&polygonMeshView);
	add(&idView);
	add(&nameView);
	add(&presenterView);
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
	auto polygonMesh = world->getScenes()->findSceneById<PolygonMeshScene*>(idView.getValue());
	polygonMesh->setName(nameView.getValue());
}