#pragma once

#include <vector>
#include "Vertex.h"
#include "VertexFactory.h"
#include "Face.h"

namespace Crystal {
	namespace Shape {
		class Face;

struct FaceGroup
{
	FaceGroup():
		id(-1)
	{}

	explicit FaceGroup(const int id) :
		id(id)
	{}

	std::list<Face*> faces;
	int id;
};

class FaceFactory
{
public:
	explicit FaceFactory(const VertexFactory& vertices) :
		vertices(vertices)
	{}

	explicit FaceFactory(FaceFactory&& rhs) :
		faces(std::move(rhs.faces)),
		vertices(rhs.vertices)
	{}

	Face* createFace(const std::array<int, 3>& indices) {
		const auto& vertices = this->vertices.getVertices();
		const auto v1 = vertices[indices[0]];
		const auto v2 = vertices[indices[1]];
		const auto v3 = vertices[indices[2]];

		auto f = new Face(v1, v2, v3);
		faces.push_back(f);
		nextGroup.faces.push_back(f);
		return f;
	}

	std::list<Face*> getFaces() const { return faces; }

	void clear()
	{
		for (auto f : faces) {
			delete f;
		}
		faces.clear();
		groups.clear();
		nextGroup = FaceGroup(0);
	}

	void pushCurrentGroup() {
		groups.push_back( nextGroup );
		nextGroup = FaceGroup(nextGroupId++);
	}

	std::vector<FaceGroup> getGroups() const { return groups; }

private:
	const VertexFactory& vertices;
	std::list<Face*> faces;
	FaceGroup nextGroup;
	int nextGroupId = 0;
	std::vector<FaceGroup> groups;
};

	}
}