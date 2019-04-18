#pragma once

#include "../Math/Box3d.h"
#include "WireFrameObject.h"
#include "IObjectRepository.h"

namespace Crystal {
	namespace Model {

class WireFrameObjectRepository : public IObjectRepository
{
public:
	explicit WireFrameObjectRepository(const ObjectIdProvider& idProvider) :
		IObjectRepository(idProvider),
		nextId(1)
	{}

	~WireFrameObjectRepository();

	void clear();

	int addObject(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	WireFrameObject* findObjectById(const int id) const;

	std::list<WireFrameObject*> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	int nextId;
	std::list<WireFrameObject*> objects;
};
	}
}