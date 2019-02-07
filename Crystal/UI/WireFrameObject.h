#pragma once

#include "IObject.h"
#include "../Shape/WireFrame.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace UI {

class WireFrameObject : public IObject
{
public:
	WireFrameObject(const int id, const std::string& name, Shape::WireFrame* shape, const Graphics::ColorRGBAf& color) :
		IObject(id, name),
		shape(shape),
		color(color)
	{}

	~WireFrameObject() {};

	Shape::WireFrame* getShape() const { return shape; }

	Graphics::ColorRGBAf getColor() const { return color; }

	void move(const Math::Vector3dd& v) override { shape->move(v); }

	void transform(const Math::Matrix3dd& m) { shape->transform(m); }

	void transform(const Math::Matrix4dd& m) { shape->transform(m); }

private:
	Shape::WireFrame* shape;
	Graphics::ColorRGBAf color;
};

	}
}