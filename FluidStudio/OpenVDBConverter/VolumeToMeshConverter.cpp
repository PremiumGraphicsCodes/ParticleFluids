#include "VolumeToMeshConverter.h"

#include <openvdb/openvdb.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "PolygonMesh.h"

using namespace Crystal::OpenVDB;

PolygonMesh VolumeToMeshConverter::toMesh(openvdb::FloatGrid grid)
{
    PolygonMesh mesh;
    openvdb::tools::volumeToMesh(grid, mesh.points, mesh.quads);
    return std::move(mesh);
}
