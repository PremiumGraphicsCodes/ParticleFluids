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

	Math::Vector3dd* createPosition(const Math::Vector3dd& v)
	{
		auto p = new Math::Vector3dd(v);
		positions.push_back(p);
		return p;
	}

	Math::Vector3dd* createNormal(const Math::Vector3dd& n)
	{
		auto nn = new Math::Vector3dd(n);
		normals.push_back(nn);
		return nn;
	}

	Math::Vector2dd* createTexCoord(const Math::Vector2dd& n)
	{
		auto tt = new Math::Vector2dd(n);
		texCoords.push_back(tt);
		return tt;
	}

	int createVertex(Math::Vector3dd* position)
	{
		Shape::VertexAttr attr;
		attr.id = nextId++;
		auto v = new Vertex(position, attr);
		vertices.push_back(v);
		return v->getAttr().id;
	}

	int createVertex(Math::Vector3dd* position, Math::Vector3dd* normal)
	{
		Shape::VertexAttr attr;
		attr.normal = normal;
		attr.id = nextId++;
		auto v = new Vertex(position, attr);
		vertices.push_back(v);
		return v->getAttr().id;
	}

	int createVertex(Math::Vector3dd* position, Math::Vector3dd* normal, Math::Vector2dd* texCoord)
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

	std::vector<Math::Vector3dd*> getPositions() const { return positions; }

	std::vector<Math::Vector3dd*> getNormals() const { return normals; }

	std::vector<Math::Vector2dd*> getTexCoords() const { return texCoords; }

private:
	int nextId;
	std::vector<Math::Vector3dd*> positions;
	std::vector<Math::Vector3dd*> normals;
	std::vector<Math::Vector2dd*> texCoords;
	std::vector<Vertex*> vertices;
};

	}
}