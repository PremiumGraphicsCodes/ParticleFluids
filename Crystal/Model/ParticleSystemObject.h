#pragma once

#include "IObject.h"
#include "../Shape/ParticleSystem.h"
#include "ParticleAttribute.h"

namespace Crystal {
	namespace Model {

class ParticleSystemObject : public IObject
{
public:
	ParticleSystemObject() :
		IObject(-1),
		shape(nullptr)
	{}

	ParticleSystemObject(const int id, const std::string& name, Shape::ParticleSystem<ParticleAttribute>* shape) :
		IObject(id, name),
		shape(shape)
	{}

	~ParticleSystemObject() {};

	Shape::ParticleSystem<ParticleAttribute>* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }

	ObjectType getType() const override { return ObjectType::ParticleSystemObject; }

private:
	Shape::ParticleSystem<ParticleAttribute>* shape;
};

	}
}