#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix3d.h"

#include "../../Crystal/Shape/IParticle.h"

namespace Crystal {
	namespace Physics {

class WPCA
{
public:
	void calculate(Shape::IParticle* center, const std::vector<Shape::IParticle*>& positions, const float radius);

	Math::Matrix3df getCovarianceMatrix() const { return covarianceMatrix; }

	Math::Vector3df getWeightedMean() const { return weightedMean; }

private :
	Math::Matrix3df calculateCovarianceMatrix(const float radius);

	Math::Vector3df calculateWeightedMean(const float radius);

	float calculateWeight(const Math::Vector3df& lhs, const Math::Vector3df& rhs, const float radius);

private:
	class PositionWeight
	{
	public:
		Math::Vector3df position;
		float weight;
	};

	std::vector<PositionWeight> pws;
	float totalWeight;

	Math::Matrix3df covarianceMatrix;
	Math::Vector3df weightedMean;
};
	}
}