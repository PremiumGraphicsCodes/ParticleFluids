#pragma once

#include "../Util/UnCopyable.h"

#include "Vertex.h"

namespace Crystal {
	namespace Shape {

class VertexFactory// : private UnCopyable
{
public:
	VertexFactory();

	~VertexFactory();

	void clear();

	Math::Vector3dd* createPosition(const Math::Vector3dd& v);

	Math::Vector3dd* createNormal(const Math::Vector3dd& n);

	Math::Vector2dd* createTexCoord(const Math::Vector2dd& n);

	Vertex* createVertex(Math::Vector3dd* position);

	Vertex* createVertex(Math::Vector3dd* position, Math::Vector3dd* normal);

	Vertex* createVertex(Math::Vector3dd* position, Math::Vector3dd* normal, Math::Vector2dd* texCoord);

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