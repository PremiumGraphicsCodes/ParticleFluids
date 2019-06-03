#include "VertexView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

VertexView::VertexView(const std::string& name) :
	IWindow(name),
	id("Id"),
	position("Position"),
	normal("Normal"),
	texCoord("TexCoord")
{
}

VertexView::VertexView(const std::string& name, Vertex* value) :
	IWindow(name),
	id("Id", value->getId()),
	position("Position"),
	normal("Normal"),
	texCoord("TexCoord")

{}

void VertexView::show()
{
	id.show();
	position.show();
	normal.show();
	texCoord.show();
}

void VertexView::setValue(Vertex* value)
{
	id.setValue(value->getId());
	position.setValue(value->getPosition());
	normal.setValue(value->getNormal());
	texCoord.setValue(value->getTexCoord());
}
