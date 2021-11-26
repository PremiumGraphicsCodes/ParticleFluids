#include "SparseVolumeBuilder.h"

#include "Crystal/Math/Sphere3d.h"
#include "Crystal/Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

void SparseVolumeBuilder::build(const Vector3df& cellLength, const size_t tableSize)
{
	this->volume = std::make_unique<SparseVolumed>(cellLength, tableSize);
}

void SparseVolumeBuilder::add(const Box3d<double>& box)
{
	const auto min = this->volume->toIndex( box.getMin() );
	const auto max = this->volume->toIndex( box.getMax() );
	for (int i = min[0]; i <= max[0]; ++i) {
		for (int j = min[1]; j <= max[1]; ++j) {
			for (int k = min[2]; k <= max[2]; ++k) {
				const std::array<int, 3> index = { i,j,k };
				if (!this->volume->exists(index)) {
					this->volume->createNode(index);
				}
			}
		}
	}
}

void SparseVolumeBuilder::add(const Sphere3d<double>& sphere)
{
	return add(sphere.getBoundingBox());
}