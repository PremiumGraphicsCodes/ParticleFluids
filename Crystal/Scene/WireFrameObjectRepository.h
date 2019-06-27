#pragma once

#include "../Math/Box3d.h"
#include "WireFrameScene.h"
#include "IObjectRepository.h"

namespace Crystal {
	namespace Model {

class WireFrameObjectRepository : public IObjectRepository
{
public:
	explicit WireFrameObjectRepository(ObjectIdProvider& idProvider) :
		IObjectRepository(idProvider)
	{}

	~WireFrameObjectRepository();

	void clear();

	int addObject(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	WireFrameScene* findObjectById(const int id) const;

	std::list<WireFrameScene*> getObjects() const { return objects; }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Vector3dd> getAllVertices() const override;

private:
	std::list<WireFrameScene*> objects;
};
	}
}