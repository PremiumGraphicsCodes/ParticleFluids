#include "PolygonFaceView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonFaceView::PolygonFaceView(const std::string& name) :
	IWindow(name),
	id("Id"),
	vertex1("Vertex1"),
	vertex2("Vertex2"),
	vertex3("Vertex3")
{
}

PolygonFaceView::PolygonFaceView(const std::string& name, Face* face) :
	IWindow(name),
	id("Id", face->getId()),
	vertex1("Vertex1", face->getV1()),
	vertex2("Vertex2", face->getV2()),
	vertex3("Vertex3", face->getV3())
{}

void PolygonFaceView::show()
{
	id.show();
	vertex1.show();
	vertex2.show();
	vertex3.show();
}

void PolygonFaceView::setValue(Face* value)
{
	id.setValue(value->getId());
	vertex1.setValue(value->getV1());
	vertex2.setValue(value->getV2());
	vertex3.setValue(value->getV3());
}
