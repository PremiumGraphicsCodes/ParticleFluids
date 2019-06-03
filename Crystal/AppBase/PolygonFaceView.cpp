#include "PolygonFaceView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonFaceView::PolygonFaceView(const std::string& name) :
	IWindow(name),
	name("Name", name),
	id("ID")
{
}

PolygonFaceView::PolygonFaceView(const std::string& name, Face* face) :
	IWindow(name),
	name("Name", name),
	id("ID", face->getId())
{}

void PolygonFaceView::show()
{
	name.show();
	id.show();
}

void PolygonFaceView::setValue(Face* value)
{
	id.setValue(value->getId());
}
