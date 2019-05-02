#include "VolumeBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

VolumeBuilder::VolumeBuilder(const int unum, const int vnum, const int wnum, const Box3d& box) :
	volume(unum, vnum, wnum, box)
{
}

void VolumeBuilder::build(const std::function<double(double)>& function)
{
	const auto& center = volume.getBoundingBox().getCenter();
}