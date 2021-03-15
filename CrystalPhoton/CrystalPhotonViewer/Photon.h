#pragma once

#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Photon {

class Photon : Shape::IParticle
{
public:
	virtual Math::Vector3dd getPosition() const { return position; }

	Graphics::ColorRGBAf getColor() const { return color; }

	float getSize() const { return size; }

private:
	Math::Vector3dd position;
	Graphics::ColorRGBAf color;
	float size;
};
	}
}