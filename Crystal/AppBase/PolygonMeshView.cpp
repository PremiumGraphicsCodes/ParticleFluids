#include "PolygonMeshView.h"

#include "../Shape/PolygonMesh.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name) :
	IWindow(name),
	name("Name", name),
	vertexCount("Verticies"),
	faceCount("Faces")
{}

void PolygonMeshView::show()
{
	name.show();
	vertexCount.show();
	faceCount.show();
}

void PolygonMeshView::setValue(PolygonMesh* value)
{
	vertexCount.setValue(value->getVertices().size());
	faceCount.setValue(value->getFaces().size());
}
