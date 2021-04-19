#include "SPHSurfaceParticle.h"

#include "WPCA.h"

#include "../../CrystalNumerics/CrystalNumerics/SVD.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

namespace {
	constexpr auto kr = 4.0;
	constexpr auto ks = 1400.0;
}

/*
void SPHSurfaceBuilder::add(IParticle* particle)
{
	this->particles.push_back(particle);
}
*/

void SPHSurfaceParticle::correctedPosition(const float lamda)
{
	this->position = (1.0f - lamda) * position + lamda * weightedMean;
}

void SPHSurfaceParticle::calculateAnisotoropicMatrix(const std::vector<IParticle*>& neighbors, const float searchRadius)
{
	//const Matrix3dd scaleMatrix;
	WPCA wpca;
	wpca.calculate(this, neighbors, searchRadius);
	this->matrix = wpca.getCovarianceMatrix();
	this->weightedMean = wpca.getWeightedMean();

	Crystal::Numerics::SVD svd;
	auto result = svd.calculateJacobi(matrix);
	/*
	if (!result.isOk) {
		p->matrix = ::identitiyMatrix();
		return;
	}
	*/

	const auto rotation = result.eigenVectors;


	Matrix3dd scaleMatrix = ::identitiyMatrix();
	if (neighbors.size() < 15) {
		scaleMatrix *= 0.5;
		//		p->matrix = scaleMatrix;
	}
	else {
		auto evs = result.eigenValues;
		evs[1] = std::max(evs[1], evs[0] / kr);
		evs[2] = std::max(evs[2], evs[0] / kr);
		evs *= ks;

		scaleMatrix = Matrix3dd
		(
			evs[0], 0.0, 0.0,
			0.0, evs[1], 0.0,
			0.0, 0.0, evs[2]
		);
	}
	this->matrix = rotation * glm::inverse(scaleMatrix) * glm::transpose(rotation) * (1.0 / searchRadius);
}

void SPHSurfaceParticle::calculateDensity(const std::vector<IParticle*>& neighbors, const float searchRadius, const SPHKernel& kernel)
{
	for (auto n : neighbors) {
		const auto distanceSquared = Math::getDistanceSquared<Vector3df>( n->getPosition(), this->position);
		this->density += kernel.getCubicSpline(::sqrt(distanceSquared));
	}
}
