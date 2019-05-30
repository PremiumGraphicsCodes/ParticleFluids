#include "FaceFactory.h"

using namespace Crystal::Shape;

FaceFactory::FaceFactory(const VertexFactory& vertices) :
	vertices(vertices)
{}

FaceFactory::FaceFactory(FaceFactory&& rhs) :
	faces(std::move(rhs.faces)),
	vertices(rhs.vertices)
{}

FaceFactory::~FaceFactory()
{
	clear();
}

void FaceFactory::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	groups.clear();
	nextGroup = FaceGroup(0);
}

Face* FaceFactory::createFace(const std::array<int, 3>& indices)
{
	const auto& vertices = this->vertices.getVertices();
	const auto v1 = vertices[indices[0]];
	const auto v2 = vertices[indices[1]];
	const auto v3 = vertices[indices[2]];

	auto f = new Face(v1, v2, v3);
	faces.push_back(f);
	nextGroup.faces.push_back(f);
	return f;
}

int FaceFactory::pushCurrentGroup(int attributeId)
{
	nextGroup.attributeId = attributeId;
	const auto id = nextGroup.id;
	groups.push_back(nextGroup);
	nextGroup = FaceGroup(nextGroupId++);
	return id;
}
