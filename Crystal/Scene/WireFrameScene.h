#pragma once

#include "IShapeScene.h"
#include "WireFrameAttribute.h"
#include "../Shape/WireFrame.h"

namespace Crystal {
	namespace Model {

class WireFrameScene : public IShapeScene
{
public:
	WireFrameScene() :
		IShapeScene(-1),
		shape(nullptr)
	{}

	WireFrameScene(const int id, const std::string& name, Shape::WireFrame* shape, const WireFrameAttribute& attribute) :
		IShapeScene(id, name),
		shape(shape),
		attribute(attribute)
	{}

	~WireFrameScene() {};

	Shape::WireFrame* getShape() const { return shape; }

	WireFrameAttribute getAttribute() const { return attribute; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }

	ObjectType getType() const override { return ObjectType::WireFrameObject; }

private:
	Shape::WireFrame* shape;
	WireFrameAttribute attribute;
};

	}
}