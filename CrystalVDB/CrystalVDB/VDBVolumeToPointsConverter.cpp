#include "VDBVolumeToPointsConverter.h"

#include "VDBVolumeScene.h"
#include "VDBVolumeImpl.h"

#include "VDBParticleSystemScene.h"
#include "VDBParticleSystemImpl.h"

//#include <openvdb/openvdb.h>

//#include <openvdb/points/PointSample.h>
//#include <openvdb/tools/VolumeToMesh.h>
#include <openvdb/points/PointConversion.h>

using namespace Crystal::VDB;

VDBParticleSystemScene* VDBVolumeToPointsConverter::toPoints(const VDBVolumeScene& volume)
{
    auto impl = volume.getImpl();
    auto grid = impl->getPtr();
    auto transform = grid->transform();
    std::vector<openvdb::Vec3f> coords;
    for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
        auto coord = transform.indexToWorld(iter.getCoord());
        coords.push_back(coord);
    }
    auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, transform);
    VDBParticleSystemScene* points = new VDBParticleSystemScene();
    points->getImpl()->setPtr(ptr);
    return points;
}
