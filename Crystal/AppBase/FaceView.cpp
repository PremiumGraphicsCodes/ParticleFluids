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
	vertex1("Vertex1", face->v1),
	vertex2("Vertex2", face->v2),
	vertex3("Vertex3", face->v3)
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
	vertex1.setValue(value->v1);
	vertex2.setValue(value->v2);
	vertex3.setValue(value->v3);
}
