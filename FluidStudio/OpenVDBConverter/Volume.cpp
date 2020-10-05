#include "Volume.h"

#include "VolumeImpl.h"

using namespace Crystal::OpenVDB;

Volume::Volume() :
	impl(std::make_unique<VolumeImpl>())
{
}
