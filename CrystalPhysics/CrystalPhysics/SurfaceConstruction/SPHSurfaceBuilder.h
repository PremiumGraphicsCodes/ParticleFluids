#pragma once

#include <vector>
#include <memory>

#include "SPHSurfaceParticle.h"

#include "Crystal/Shape/Volume.h"
#include "../../../CrystalSpace/CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace Physics {


class SPHSurfaceBuilder
{
public:
	//void add(Shape::IParticle* particle);

	void buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	void buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

	const std::vector<std::unique_ptr<SPHSurfaceParticle>>& getParticles() const { return particles; }

	std::vector < Shape::Volume<double>* > getVolumes() { return volumes; }

	std::unique_ptr<Space::SparseVolumed> getVolume() { return std::move(volume); }

private:
	std::unique_ptr<Space::SparseVolumed> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float cellLength);

	void calculateAnisotropy(const float searchRadius);
	
	//std::vector<Shape::IParticle*> particles;

	std::vector<Shape::Volume<double>*> volumes;

	std::unique_ptr<Space::SparseVolumed> volume;
	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
};
	}
}