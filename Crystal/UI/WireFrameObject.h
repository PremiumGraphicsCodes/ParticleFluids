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

private:
	Shape::WireFrame* shape;
	Graphics::ColorRGBAf color;
};

	}
}