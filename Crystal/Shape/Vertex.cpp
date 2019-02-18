#include "stdafx.h"
#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Vertex::Vertex(const Vector3df& position,const VertexAttr& attr) :
	position(position),
	attr(attr)
{}

Vertex* Vertex::clone()
{
	return new Vertex(getPosition(), attr);
}

Box3d Util::getBoundingBox(const std::list<Vertex*>& vertices)
{
	Box3d box(vertices.front()->getPosition());
	for (auto v : vertices) {
		box.add(v->getPosition());
	}
	return box;
}