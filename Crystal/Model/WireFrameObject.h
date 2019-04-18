#pragma once

#include "IObject.h"
#include "WireFrameAttribute.h"
#include "../Shape/WireFrame.h"

namespace Crystal {
	namespace Model {

class WireFrameObject : public IObject
{
public:
	WireFrameObject() :
		IObject(-1),
		shape(nullptr)
	{}

	WireFrameObject(const int id, const std::string& name, Shape::WireFrame* shape, const WireFrameAttribute& attribute) :
		IObject(id, name),
		shape(shape),
		attribute(attribute)
	{}

	~WireFrameObject() {};

	Shape::WireFrame* getShape() const { return shape; }

	WireFrameAttribute getAttribute() const { return attribute; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

	bool isNull() const { return shape == nullptr; }


private:
	Shape::WireFrame* shape;
	WireFrameAttribute attribute;
};

	}
}