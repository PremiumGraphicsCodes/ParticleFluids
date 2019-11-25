#include "PolygonMeshView.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name) :
	IWindow(name),
	vertexCount("Verticies"),
	faceCount("Faces")
{}

void PolygonMeshView::onShow()
{
	vertexCount.show();
	faceCount.show();
}

void PolygonMeshView::setValue(PolygonMesh* value)
{
	vertexCount.setValue(value->getVertices().size());
	faceCount.setValue(value->getFaces().size());
}
