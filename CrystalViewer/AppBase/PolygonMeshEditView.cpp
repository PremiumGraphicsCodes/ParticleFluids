#include "PolygonMeshEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	polygonMesh("PolygonMesh"),
	world(repository),
	id("Id"),
	name("Name"),
	edit("Edit")
{
	edit.setFunction([=]() { onEdit(); });
}

void PolygonMeshEditView::onShow()
{
	polygonMesh.show();
	id.show();
	name.show();
	edit.show();
}

void PolygonMeshEditView::setValue(PolygonMeshScene* value)
{
	polygonMesh.setValue(value->getShape());
	id.setValue(value->getId());
	name.setValue(value->getName());
}

void PolygonMeshEditView::onEdit()
{
	auto polygonMesh = world->getObjects()->findSceneById<PolygonMeshScene*>(id.getValue());
	polygonMesh->setName(name.getValue());
}