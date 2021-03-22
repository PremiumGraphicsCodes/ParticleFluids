#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Matrix3d.h"

//#include "../../Crystal/Shape/IP"

namespace Crystal {
	namespace Physics {

class WPCA
{
public:
	Math::Matrix3df calculate(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

private :
	Math::Matrix3df calculateCovarianceMatrix(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

	Math::Vector3df calculateWeightedMean(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius);

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
};
	}
}