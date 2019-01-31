#pragma once

#include "../Math/Box3d.h"
#include "WireFrameObject.h"

namespace Crystal {
	namespace UI {

class WireFrameObjectRepository
{
public:
	WireFrameObjectRepository() :
		nextId(1)
	{}

	~WireFrameObjectRepository();

	void clear();

	int addObject(Shape::WireFrame* wire, const Graphics::ColorRGBAf& color, const std::string& name);

	std::list<WireFrameObject> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const;

	std::list<Math::Vector3dd> getAllVertices() const;

private:
	int nextId;
	std::list<WireFrameObject> objects;
};
	}
}