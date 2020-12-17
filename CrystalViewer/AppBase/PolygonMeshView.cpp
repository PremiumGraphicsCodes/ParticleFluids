#include "PolygonMeshView.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name) :
	IView(name),
	vertexCount("Verticies"),
	faceCount("Faces")
{
	add(&vertexCount);
	add(&faceCount);
}

void PolygonMeshView::setValue(PolygonMesh* value)
{
	vertexCount.setValue(static_cast<int>( value->getVertices().size()));
	faceCount.setValue(static_cast<int>( value->getFaces().size()) );
}
