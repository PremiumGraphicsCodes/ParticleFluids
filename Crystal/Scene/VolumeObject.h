#pragma once

#include "IScene.h"
#include "../Shape/Volume.h"
#include "ParticleAttribute.h"

namespace Crystal {
	namespace Model {

class VolumeObject : public IScene
{
public:
	VolumeObject() :
		IScene(-1),
		shape(nullptr)
	{}

	VolumeObject(const int id, const std::string& name, Shape::Volume* shape) :
		IScene(id, name),
		shape(shape)
	{}

	~VolumeObject() {};

	Shape::Volume* getShape() const { return shape; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }

	SceneType getType() const override { return SceneType::VolumeObjectObject; }

private:
	Shape::Volume* shape;
};

	}
}