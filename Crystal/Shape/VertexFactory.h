#pragma once

#include "../Util/UnCopyable.h"

#include "Vertex.h"

namespace Crystal {
	namespace Shape {

class VertexFactory : private UnCopyable
{
public:
	VertexFactory() :
		nextId(0)
	{}

	VertexFactory(VertexFactory&& rhs) :
		nextId(rhs.nextId),
		vertices(std::move(rhs.vertices))
	{
	}

	int createVertex(const Math::Vector3dd& position)
	{
		Shape::VertexAttr attr;
		attr.id = nextId++;
		auto v = new Vertex(position, attr);
		vertices.push_back(v);
		return v->getAttr().id;
	}

	int createVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal)
	{
		Shape::VertexAttr attr;
		attr.normal = normal;
		attr.id = nextId++;
		auto v = new Vertex(position, attr);
		vertices.push_back(v);
		return v->getAttr().id;
	}

	int createVertex(const Math::Vector3dd& position, const Math::Vector3dd& normal, const Math::Vector2dd& texCoord)
	{
		Shape::VertexAttr attr;
		attr.normal = normal;
		attr.texCoord = texCoord;
		attr.id = nextId++;
		auto v = new Vertex(position, attr);
		vertices.push_back(v);
		return v->getAttr().id;
	}

	std::vector<Vertex*> getVertices() const { return vertices; }

private:
	int nextId;
	std::vector<Vertex*> vertices;
};

	}
}