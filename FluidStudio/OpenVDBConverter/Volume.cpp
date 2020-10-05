#include "Volume.h"

#include "VolumeImpl.h"

using namespace Crystal::OpenVDB;

Volume::Volume() :
	impl(new VolumeImpl())
{
}

Volume::Volume(const float value)
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>(value);
	impl = new VolumeImpl(grid);
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
