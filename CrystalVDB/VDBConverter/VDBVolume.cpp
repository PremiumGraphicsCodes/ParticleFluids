#include "VDBVolume.h"

#include "VolumeImpl.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

using namespace openvdb;

VDBVolume::VDBVolume() :
	IShapeScene(-1, ""),
	impl(new VolumeImpl())
{
	impl->setPtr(FloatGrid::create());
}

VDBVolume::VDBVolume(VolumeImpl* impl) :
	IShapeScene(-1, "")
{
	this->impl = impl;
}


VDBVolume::VDBVolume(const float value) :
	IShapeScene(-1, "")
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

	//impl->getPtr()->tree().
}

void VDBVolume::setValue(const std::array<int, 3>& index, const float value)
{
	math::Coord coord(index[0], index[1], index[2]);
	impl->getPtr()->getAccessor().setValue(coord, value);
}

float VDBVolume::getValue(const std::array<int, 3> index)
{
	math::Coord coord(index[0], index[1], index[2]);
	return impl->getPtr()->getAccessor().getValue(coord);
}

int VDBVolume::getActiveVoxelCount() const
{
	return impl->getPtr()->activeVoxelCount();
}

VDBVolume::~VDBVolume()
{
	delete impl;
}

/*
Crystal::Shape::ParticleSystem* VDBVolume::toCrystalParticleSystem()
{
	for (auto iter = impl->getPtr()->beginValueAll(); ; ++iter) {
		*(iter).getCoord()
	}
}
*/
