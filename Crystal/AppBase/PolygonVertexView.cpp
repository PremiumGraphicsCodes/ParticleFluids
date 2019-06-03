#include "PolygonVertexView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

PolygonVertexView::PolygonVertexView(const std::string& name) :
	IWindow(name),
	id("Id"),
	position("Position"),
	normal("Normal"),
	texCoord("TexCoord")
{
}

PolygonVertexView::PolygonVertexView(const std::string& name, Vertex* value) :
	IWindow(name),
	id("Id", value->getId()),
	position("Position"),
	normal("Normal"),
	texCoord("TexCoord")

{}

void PolygonVertexView::show()
{
	id.show();
	position.show();
	normal.show();
	texCoord.show();
}

void PolygonVertexView::setValue(Vertex* value)
{
	id.setValue(value->getId());
	position.setValue(value->getPosition());
	normal.setValue(value->getNormal());
	texCoord.setValue(value->getTexCoord());
}
