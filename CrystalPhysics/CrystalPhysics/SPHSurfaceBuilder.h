#pragma once

#include <vector>
#include <memory>

#include "SPHSurfaceParticle.h"

#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace Physics {


class SPHSurfaceBuilder
{
public:
	//void add(Shape::IParticle* particle);

	void buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius);

	void buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius, const float cellLength);

	const std::vector<std::unique_ptr<SPHSurfaceParticle>>& getParticles() const { return particles; }

	std::unique_ptr<Space::SparseVolume> getVolume() { return std::move(volume); }

private:
	std::unique_ptr<Space::SparseVolume> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float searchRadius, const float cellLength);

	
	//std::vector<Shape::IParticle*> particles;

	std::unique_ptr<Space::SparseVolume> volume;
	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
};
	}
}