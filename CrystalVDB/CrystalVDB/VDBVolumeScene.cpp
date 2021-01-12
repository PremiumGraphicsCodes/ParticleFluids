#include "VDBVolumeScene.h"

#include "VDBVolumeImpl.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

using namespace openvdb;

VDBVolumeScene::VDBVolumeScene() :
	IShapeScene(-1, ""),
	impl(new VDBVolumeImpl())
{
	impl->setPtr(FloatGrid::create());
	presenter = std::make_unique<VDBVolumePresenter>(this);
}

VDBVolumeScene::VDBVolumeScene(VDBVolumeImpl* impl) :
	IShapeScene(-1, "")
{
	this->impl = impl;
	presenter = std::make_unique<VDBVolumePresenter>(this);
}

VDBVolumeScene::VDBVolumeScene(const float value) :
	IShapeScene(-1, "")
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>(value);
	impl = new VDBVolumeImpl(grid);
	presenter = std::make_unique<VDBVolumePresenter>(this);
}

VDBVolumeScene::VDBVolumeScene(const int id, const std::string& name) :
	IShapeScene(id, name)
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>();
	impl = new VDBVolumeImpl(grid);
	impl->setPtr(FloatGrid::create());
	presenter = std::make_unique<VDBVolumePresenter>(this);
}


void VDBVolumeScene::fill(const unsigned int coord1, const unsigned int coord2, const float value)
{
	openvdb::CoordBBox bbox;// openvdb::Coord(Int32(coord1)), openvdb::Coord(Int32(coord2)));
	bbox.reset(Coord(coord1), Coord(coord2));
	impl->getPtr()->tree().fill(bbox, value);

	//impl->getPtr()->tree().
}

void VDBVolumeScene::setValue(const std::array<int, 3>& index, const float value)
{
	math::Coord coord(index[0], index[1], index[2]);
	impl->getPtr()->getAccessor().setValue(coord, value);
}

float VDBVolumeScene::getValue(const std::array<int, 3> index)
{
	math::Coord coord(index[0], index[1], index[2]);
	return impl->getPtr()->getAccessor().getValue(coord);
}

int VDBVolumeScene::getActiveVoxelCount() const
{
	return impl->getPtr()->activeVoxelCount();
}

Box3d VDBVolumeScene::getBoundingBox() const
{
	auto grid = impl->getPtr();
	auto transform = grid->transform();
	auto firstPos = transform.indexToWorld( grid->cbeginValueOn().getCoord() );
	Box3d bb(Converter::fromVDB(firstPos));
	for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
		auto coord = transform.indexToWorld(iter.getCoord());
		bb.add(Converter::fromVDB(coord));
	}
	return bb;
}

VDBVolumeScene::~VDBVolumeScene()
{
	delete impl;
}
