#pragma once

#include "IObject.h"
#include "../Shape/Volume.h"
#include "ParticleAttribute.h"

namespace Crystal {
	namespace Model {

class VolumeObject : public IObject
{
public:
	VolumeObject() :
		IObject(-1),
		shape(nullptr)
	{}

	VolumeObject(const int id, const std::string& name, Shape::Volume* shape) :
		IObject(id, name),
		shape(shape)
	{}

	~VolumeObject() {};

	Shape::Volume* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }

	ObjectType getType() const override { return ObjectType::VolumeObjectObject; }

private:
	Shape::Volume* shape;
};

	}
}