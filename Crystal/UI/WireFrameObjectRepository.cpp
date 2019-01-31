#include "WireFrameObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

WireFrameObjectRepository::~WireFrameObjectRepository()
{
	clear();
}

void WireFrameObjectRepository::clear()
{
	for (auto w : objects) {
		delete w.getShape();
	}
	objects.clear();
}

int WireFrameObjectRepository::addObject(WireFrame* wire, const ColorRGBAf& color, const std::string& name)
{
	objects.push_back(WireFrameObject(nextId++, name, wire, color));
	return objects.back().getId();
}

Box3d WireFrameObjectRepository::getBoundingBox() const
{
	const auto& vertices = getAllVertices();
	if (vertices.empty()) {
		return Box3d();
	}
	Box3d bb(vertices.front());
	for (const auto& v : vertices) {
		bb.add(v);
	}
	return bb;
}

std::list<Vector3dd> WireFrameObjectRepository::getAllVertices() const
{
	std::list<Vector3dd> positions;
	for (const auto& ws : objects) {
		const auto& vs = ws.getShape()->getVertices();
		positions.insert(positions.end(), vs.begin(), vs.end());
	}
	return positions;
}
