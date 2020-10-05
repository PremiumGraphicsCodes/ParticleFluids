#include "Volume.h"

#include "VolumeImpl.h"

using namespace Crystal::OpenVDB;

Volume::Volume() :
	impl(new VolumeImpl())
{
}

/*
Volume::Volume(std::unique_ptr<VolumeImpl> impl) :
	impl(std::move(impl))
{}
*/

Volume::~Volume()
{
	delete impl;
}
