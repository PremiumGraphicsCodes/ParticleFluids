#pragma once

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class MPSParticle : public Shape::IParticle
{
public:
	Math::Vector3dd getPosition() const override { return position; }

	Math::Vector3df getPositionf() const { return position; }

	Math::Vector3df getVelocity() const { return velocity; }

	float getPressure() const { return pressure; }

	float getRestDensity() const { return n0; }

	float getLamda0() const { return lamda0; }

private:
	float pressure;
	float n0;
	float lamda0;
	Math::Vector3df position;
	Math::Vector3df velocity;
};

	}
}