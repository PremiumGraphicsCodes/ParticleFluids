#include "PolygonMeshView.h"

#include "../Shape/PolygonMesh.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name, PolygonMesh* mesh) :
	IWindow(name),
	name("Name", name),
	vertexCount("Verticies", mesh->getVertices().size()),
	faceCount("Faces", mesh->getFaces().size()),
	value(mesh)
{}

void PolygonMeshView::show()
{
	name.show();
	vertexCount.show();
	faceCount.show();
}
