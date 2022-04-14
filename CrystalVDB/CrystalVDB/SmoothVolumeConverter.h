#pragma once

#include <vector>
#include <memory>

#include "Crystal/Shape/Volume.h"
#include "CrystalSpace/CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace Physics {

class SmoothVolumeConverter
{
public:
	//void add(Shape::IParticle* particle);

	std::unique_ptr<Space::SparseVolumef> buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float particleRadius, const float cellLength);

private:
};

	}
}