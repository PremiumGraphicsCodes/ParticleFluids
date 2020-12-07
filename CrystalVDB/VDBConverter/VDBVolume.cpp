#include "VDBVolume.h"

#include "VolumeImpl.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

using namespace openvdb;

VDBVolume::VDBVolume() :
	impl(new VolumeImpl())
{
}

VDBVolume::VDBVolume(const float value)
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>(value);
	impl = new VolumeImpl(grid);
}

void VDBVolume::fill(const unsigned int coord1, const unsigned int coord2, const float value)
{
	openvdb::CoordBBox bbox;// openvdb::Coord(Int32(coord1)), openvdb::Coord(Int32(coord2)));
	bbox.reset(Coord(coord1), Coord(coord2));
	impl->getPtr()->tree().fill(bbox, value);
}


/*
Volume::Volume(std::unique_ptr<VolumeImpl> impl) :
	impl(std::move(impl))
{}
*/

VDBVolume::~VDBVolume()
{
	delete impl;
}

/*
Crystal::Scene::ParticleSystemScene* Volume::toCrystalParticleSystem()
{
	impl->getPtr()->
}
*/
