#include "OpenVDBFileWriter.h"

#include <openvdb/points/PointConversion.h>

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

//openvdb::Vec3R


void OpenVDBFileWriter::write(const std::string& filename)
{
    std::vector<openvdb::Vec3R> ps = Converter::toVDB(positions);
    openvdb::points::PointAttributeVector<openvdb::Vec3R> positionsWrapper(ps);

    int pointsPerVoxel = 8;
    float voxelSize = openvdb::points::computeVoxelSize(positionsWrapper, pointsPerVoxel);

    auto transform = openvdb::math::Transform::createLinearTransform(voxelSize);
    auto grid = openvdb::points::createPointDataGrid
        <
        openvdb::points::NullCodec,
        openvdb::points::PointDataGrid
        >
        (ps, *transform);

    grid->setName(name);

    openvdb::io::File file(filename);
    file.write({ grid });
    file.close();
}
