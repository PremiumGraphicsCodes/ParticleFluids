#include "PolygonMeshView.h"

#include "../Shape/PolygonMesh.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name, PolygonMesh* mesh) :
	IWindow(name),
	name("Name", name),
	vertexCount("Verticies", mesh->getVertices().size()),
	groupCount("Groups", mesh->getGroups().size()),
	value(mesh)
{}

void PolygonMeshView::show()
{
	name.show();
	vertexCount.show();
	groupCount.show();
}
