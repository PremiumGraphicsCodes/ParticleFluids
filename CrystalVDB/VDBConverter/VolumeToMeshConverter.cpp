#include "VolumeToMeshConverter.h"

#include <openvdb/openvdb.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "VolumeImpl.h"
#include "PolygonMeshImpl.h"

using namespace Crystal::VDB;

VDBPolygonMesh* VolumeToMeshConverter::toMesh(const VDBVolume& volume)
{   
    auto mesh = new VDBPolygonMesh();
    auto impl = mesh->getImpl();
    auto grid = volume.getImpl()->getPtr();
    openvdb::tools::volumeToMesh(*grid, impl->points, impl->quads);
    return mesh;
}