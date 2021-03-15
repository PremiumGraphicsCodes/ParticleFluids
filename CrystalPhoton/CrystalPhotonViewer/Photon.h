#pragma once

#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Photon {

class Photon : Shape::IParticle
{
public:
	virtual Math::Vector3dd getPosition() const { return position; }

private:
	Math::Vector3dd position;
};
	}
}