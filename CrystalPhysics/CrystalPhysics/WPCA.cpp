#include "WPCA.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	class PositionWeight
	{
	public:
		Vector3df position;
		float weight;
	};
}

Vector3df WPCA::calculateWeightedMean(const Math::Vector3df& center, const std::vector<Math::Vector3df>& positions, const float radius)
{
	std::vector<PositionWeight> pws;
	pws.reserve(positions.size());
	for (const auto& p : positions) {
		const auto w = calculateWeight(center, p, radius);
		PositionWeight pw;
		pw.position = p;
		pw.weight = w;
		pws.push_back(pw);
	}

	float totalWeight = 0.0f;
	for (const auto& pw : pws) {
		totalWeight += pw.weight;
	}

	Vector3df weightedCenter(0.0f, 0.0f, 0.0f);
	for (const auto pw : pws) {
		weightedCenter += pw.position * pw.weight;
	}
	weightedCenter /= totalWeight;

	return Vector3df();
}

float WPCA::calculateWeight(const Vector3df& lhs, const Vector3df& rhs, const float radius)
{
	const auto distance = Crystal::Math::getDistanceSquared(lhs, rhs);
	if (distance > radius) {
		return 0.0f;
	}
	return 1.0f - std::pow((distance / radius), 3.0f);
}
