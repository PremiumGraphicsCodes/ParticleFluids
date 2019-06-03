#include "FaceFactory.h"

using namespace Crystal::Shape;

FaceFactory::FaceFactory(const VertexFactory& vertices) :
	vertices(vertices)
{}

FaceFactory::~FaceFactory()
{
}

void FaceFactory::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	groups.clear();
	nextFaceId = 0;
	nextGroup = FaceGroup(0);
	nextGroupId = 0;
}

Face* FaceFactory::createFace(const std::array<int, 3>& indices)
{
	const auto& vertices = this->vertices.getVertices();
	const auto v1 = vertices[indices[0]];
	const auto v2 = vertices[indices[1]];
	const auto v3 = vertices[indices[2]];

	auto f = new Face(v1, v2, v3, nextFaceId++);
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

FaceGroup FaceFactory::findGroupByFace(Face* f) const
{
	auto iter = std::find_if(groups.cbegin(), groups.cend(), [=](auto g) { return g.has(f); });
	assert( iter != groups.cend() );
	return *iter;
}
