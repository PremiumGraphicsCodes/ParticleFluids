#include "VolumeToMeshConverter.h"

#include <openvdb/openvdb.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "VolumeImpl.h"
#include "PolygonMeshImpl.h"

using namespace Crystal::VDB;

std::unique_ptr<VDBPolygonMesh> VolumeToMeshConverter::toMesh(const VDBVolume& volume)
{   
    auto mesh = std::make_unique<VDBPolygonMesh>();
    auto impl = mesh->getImpl();
    auto grid = volume.getImpl()->getPtr();
    openvdb::tools::volumeToMesh(*grid, impl->points, impl->quads);
    return std::move(mesh);
}
