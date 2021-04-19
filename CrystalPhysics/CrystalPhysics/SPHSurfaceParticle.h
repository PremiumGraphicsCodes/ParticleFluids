#pragma once

#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : public Shape::IParticle
{
public:
	explicit SPHSurfaceParticle(const Math::Vector3dd& p) :
		position(p),
		correctedPosition(p),
		matrix(Math::identitiyMatrix())
	{}

	Math::Vector3dd getPosition() const { return position; }

	Math::Matrix3dd matrix;

	void calculateCorrectedPosition(const float lamda);

	void calculateAnisotoropicMatrix(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius);

	Math::Vector3df getCorrectedPosition() const { return correctedPosition; }

private:
	Math::Vector3df position;
	Math::Vector3df correctedPosition;
	Math::Vector3df weightedMean;
};

	}
}