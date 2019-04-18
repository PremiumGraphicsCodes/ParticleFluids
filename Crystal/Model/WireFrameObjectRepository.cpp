#include "WireFrameObjectRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Model;

WireFrameObjectRepository::~WireFrameObjectRepository()
{
	clear();
}

void WireFrameObjectRepository::clear()
{
	for (auto w : objects) {
		delete w->getShape();
		delete w;
	}
	objects.clear();
}

int WireFrameObjectRepository::addObject(WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name)
{
	objects.push_back(new WireFrameObject(getNextId(), name, wire, attribute));
	return objects.back()->getId();
}

WireFrameObject* WireFrameObjectRepository::findObjectById(const int id) const
{
	auto iter = std::find_if(std::cbegin(objects), std::cend(objects), [=](auto p) {return p->getId() == id; });
	if (iter == std::cend(objects)) {
		return nullptr;
	}
	return *iter;
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
	for (auto ws : objects) {
		const auto& vs = ws->getShape()->getVertices();
		positions.insert(positions.end(), vs.begin(), vs.end());
	}
	return positions;
}
