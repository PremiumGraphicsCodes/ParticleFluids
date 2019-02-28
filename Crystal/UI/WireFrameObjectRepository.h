#pragma once

#include "../Math/Box3d.h"
#include "WireFrameObject.h"
#include "IObjectRepository.h"

namespace Crystal {
	namespace UI {

class WireFrameObjectRepository : public IObjectRepository
{
public:
	WireFrameObjectRepository() :
		nextId(1)
	{}

	~WireFrameObjectRepository();

	void clear();

	int addObject(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	std::list<WireFrameObject> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	int nextId;
	std::list<WireFrameObject> objects;
};
	}
}