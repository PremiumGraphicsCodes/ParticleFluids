#include "stdafx.h"
#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Vertex::Vertex(const Vector3df& position) :
	position(position)
{}

Vertex::Vertex(const Vector3df& position, const Vector3df& normal) :
	position(position),
	normal(normal)
{}

Vertex::Vertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord) :
	position(position),
	normal(normal),
	texCoord(texCoord)
{}

Vertex* Vertex::clone()
{
	return new Vertex(getPosition(), getNormal());
}

void Vertex::reverse()
{
	this->normal = (-getNormal());
}

Box3d Util::getBoundingBox(const std::list<Vertex*>& vertices)
{
	Box3d box(vertices.front()->getPosition());
	for (auto v : vertices) {
		box.add(v->getPosition());
	}
	return box;
}