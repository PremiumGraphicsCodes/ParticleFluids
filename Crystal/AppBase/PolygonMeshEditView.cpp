#include "PolygonMeshEditView.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshEditView::PolygonMeshEditView(const std::string& name, Repository* repository, Canvas* canvas) :
	IWindow(name),
	polygonMesh("PolygonMesh"),
	id("Id"),
	name("Name"),
	materialName("MaterialName")
{
}

void PolygonMeshEditView::show()
{
	polygonMesh.show();
	id.show();
	name.show();
	materialName.show();
}

void PolygonMeshEditView::setValue(PolygonMeshScene* value)
{
	polygonMesh.setValue(value->getShape());
	id.setValue(value->getId());
	name.setValue(value->getName());
	materialName.setValue( value->getMaterialName() );
}