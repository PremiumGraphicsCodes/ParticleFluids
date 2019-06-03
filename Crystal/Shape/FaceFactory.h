#pragma once

#include <vector>
#include "Vertex.h"
#include "VertexFactory.h"
#include "Face.h"
#include "FaceGroup.h"

namespace Crystal {
	namespace Shape {
		class Face;

class FaceFactory
{
public:
	explicit FaceFactory(const VertexFactory& vertices);

	explicit FaceFactory(FaceFactory&& rhs);

	~FaceFactory();

	Face* createFace(const std::array<int, 3>& indices);

	std::list<Face*> getFaces() const { return faces; }

	void clear();

	int pushCurrentGroup(int attributeId = -1);

	std::vector<FaceGroup> getGroups() const { return groups; }

private:
	const VertexFactory& vertices;
	std::list<Face*> faces;
	FaceGroup nextGroup;
	int nextGroupId = 0;
	int nextFaceId = 0;
	std::vector<FaceGroup> groups;
};

	}
}