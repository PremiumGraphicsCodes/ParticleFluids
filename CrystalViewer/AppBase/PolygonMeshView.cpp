#include "PolygonMeshView.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonMeshView::PolygonMeshView(const std::string& name) :
	IView(name),
	vertexCount("Verticies"),
	faceCount("Faces"),
	presenterView("Presenter")
{
	add(&vertexCount);
	add(&faceCount);
	add(&presenterView);
	//std::function<void()> onPresenterChanged = []() { return 1; };
	presenterView.add("Smooth");
	presenterView.add("Wire");
}

void PolygonMeshView::setValue(PolygonMesh* value)
{
	vertexCount.setValue(static_cast<int>( value->getVertices().size()));
	faceCount.setValue(static_cast<int>( value->getFaces().size()) );
}
