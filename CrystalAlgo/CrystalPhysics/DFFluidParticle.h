#pragma once

#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Physics {

class DFFluidParticle : Shape::IPoint
{
public:
	explicit DFFluidParticle(const Math::Vector3dd& position) :
		position(position)
	{}

	Math::Vector3dd getPosition() const override { return position; }

private:
	Math::Vector3dd position;
};
	}
}