#include "VDBVolumeConverter.h"

#include <openvdb/openvdb.h>

#include <openvdb/points/PointSample.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "VolumeImpl.h"
#include "PolygonMeshImpl.h"
#include "VDBParticleSystemImpl.h"

#include "VDBParticleSystem.h"

using namespace Crystal::VDB;

void VDBVolumeConverter::toMesh(const VDBVolume& volume, VDBPolygonMesh* mesh)
{   
    auto impl = mesh->getImpl();
    impl->clear();
    auto grid = volume.getImpl()->getPtr();
    openvdb::tools::volumeToMesh(*grid, impl->points, impl->getQuads());
    impl->updateNormals();
}

void VDBVolumeConverter::toParticleSystem(const VDBVolume& volume, VDBParticleSystem* ps) const
{
    auto impl = volume.getImpl();
    auto grid = impl->getPtr();
    auto transform = grid->transform();
    for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
        auto coord = transform.indexToWorld(iter.getCoord());
        ps->getImpl()->add(coord, 1.0);
    }
}
