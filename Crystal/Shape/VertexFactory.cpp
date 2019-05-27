#include "VertexFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

VertexFactory::VertexFactory() :
	nextId(0)
{}

VertexFactory::VertexFactory(VertexFactory&& rhs) :
	nextId(rhs.nextId),
	vertices(std::move(rhs.vertices))
{
}

VertexFactory::~VertexFactory()
{
	clear();
}

void VertexFactory::clear()
{
	nextId = 0;
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
	for (auto p : positions) {
		delete p;
	}
	positions.clear();
	for (auto n : normals) {
		delete n;
	}
	normals.clear();
	for (auto t : texCoords) {
		delete t;
	}
	texCoords.clear();
}

Vector3dd* VertexFactory::createPosition(const Vector3dd& v)
{
	auto p = new Math::Vector3dd(v);
	positions.push_back(p);
	return p;
}

Vector3dd* VertexFactory::createNormal(const Vector3dd& n)
{
	auto nn = new Math::Vector3dd(n);
	normals.push_back(nn);
	return nn;
}

Vector2dd* VertexFactory::createTexCoord(const Vector2dd& n)
{
	auto tt = new Math::Vector2dd(n);
	texCoords.push_back(tt);
	return tt;
}

int VertexFactory::createVertex(Vector3dd* position)
{
	Shape::VertexAttr attr;
	attr.id = nextId++;
	auto v = new Vertex(position, attr);
	vertices.push_back(v);
	return v->getAttr().id;
}

int VertexFactory::createVertex(Vector3dd* position, Vector3dd* normal)
{
	Shape::VertexAttr attr;
	attr.normal = normal;
	attr.id = nextId++;
	auto v = new Vertex(position, attr);
	vertices.push_back(v);
	return v->getAttr().id;
}

int VertexFactory::createVertex(Vector3dd* position, Vector3dd* normal, Vector2dd* texCoord)
{
	Shape::VertexAttr attr;
	attr.normal = normal;
	attr.texCoord = texCoord;
	attr.id = nextId++;
	auto v = new Vertex(position, attr);
	vertices.push_back(v);
	return v->getAttr().id;
}
