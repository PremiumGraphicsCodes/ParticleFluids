#pragma once

#include "IScene.h"
#include "../Shape/Volume.h"
#include "ParticleAttribute.h"

namespace Crystal {
	namespace Scene {

class VolumeScene : public IScene
{
public:
	VolumeScene() :
		IScene(-1),
		shape(nullptr)
	{}

	VolumeScene(const int id, const std::string& name, Shape::Volume* shape) :
		IScene(id, name),
		shape(shape)
	{}

	~VolumeScene() {};

	Shape::Volume* getShape() const { return shape; }

	/*
	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }
	*/

	SceneType getType() const override { return SceneType::VolumeScene; }

	void onClear() override
	{
		delete shape;
	}

private:
	Shape::Volume* shape;
};

	}
}