#include "VDBVolumeConverter.h"

#include <openvdb/openvdb.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "VolumeImpl.h"
#include "PolygonMeshImpl.h"

using namespace Crystal::VDB;

void VDBVolumeConverter::toMesh(const VDBVolume& volume, VDBPolygonMesh* mesh)
{   
    auto impl = mesh->getImpl();
    impl->clear();
    auto grid = volume.getImpl()->getPtr();
    openvdb::tools::volumeToMesh(*grid, impl->points, impl->quads);
    impl->updateNormals();
}