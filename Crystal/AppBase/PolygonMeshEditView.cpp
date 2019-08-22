#include "PolygonMeshEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	polygonMesh("PolygonMesh"),
	id("Id"),
	name("Name"),
	edit("Edit")
{
	edit.setFunction([=]() { onEdit(); });
}

void PolygonMeshEditView::show()
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

}