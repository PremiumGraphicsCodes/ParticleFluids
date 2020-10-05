#include "VolumeToMeshConverter.h"

#include <openvdb/openvdb.h>

#include "openvdb/tools/VolumeToMesh.h"

#include "PolygonMeshImpl.h"

using namespace Crystal::OpenVDB;

PolygonMeshImpl VolumeToMeshConverter::toMesh(openvdb::FloatGrid grid)
{
    PolygonMeshImpl mesh;
    openvdb::tools::volumeToMesh(grid, mesh.points, mesh.quads);
    return std::move(mesh);
}
