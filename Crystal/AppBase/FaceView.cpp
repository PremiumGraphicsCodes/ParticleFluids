#include "FaceView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

FaceView::FaceView(const std::string& name) :
	IWindow(name),
	id("Id"),
	vertex1("Vertex1"),
	vertex2("Vertex2"),
	vertex3("Vertex3")
{
}

FaceView::FaceView(const std::string& name, Face* face) :
	IWindow(name),
	id("Id", face->id),
	vertex1("Vertex1", face->getV1()),
	vertex2("Vertex2", face->getV2()),
	vertex3("Vertex3", face->getV3())
{}

void FaceView::show()
{
	id.show();
	vertex1.show();
	vertex2.show();
	vertex3.show();
}

void FaceView::setValue(Face* value)
{
	id.setValue(value->id);
	vertex1.setValue(value->getV1());
	vertex2.setValue(value->getV2());
	vertex3.setValue(value->getV3());
}
