#include "OpenVDBFileWriter.h"

#include <openvdb/openvdb.h>
#include <openvdb/points/PointConversion.h>

using namespace Crystal::OpenVDB;

void OpenVDBFileWriter::write(const std::string& filename)
{
    openvdb::points::PointAttributeVector<openvdb::Vec3R> positionsWrapper(positions);

    int pointsPerVoxel = 8;
    float voxelSize = openvdb::points::computeVoxelSize(positionsWrapper, pointsPerVoxel);

    auto transform = openvdb::math::Transform::createLinearTransform(voxelSize);
    auto grid = openvdb::points::createPointDataGrid
        <
        openvdb::points::NullCodec,
        openvdb::points::PointDataGrid
        >
        (positions, *transform);

    grid->setName(name);

    openvdb::io::File file(filename);
    file.write({ grid });
    file.close();
}
