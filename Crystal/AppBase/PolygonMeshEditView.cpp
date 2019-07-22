#include "PolygonMeshEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	polygonMesh("PolygonMesh"),
	id("Id"),
	name("Name")
{
}

void PolygonMeshEditView::show()
{
	polygonMesh.show();
	id.show();
	name.show();
}

void PolygonMeshEditView::setValue(PolygonMeshScene* value)
{
	this->polygonMesh.setValue(value->getShape());
	this->id.setValue(value->getId());
	this->name.setValue(value->getName());
}