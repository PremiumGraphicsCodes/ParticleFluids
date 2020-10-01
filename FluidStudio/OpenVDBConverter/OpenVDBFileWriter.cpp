#include "OpenVDBFileWriter.h"

#include <openvdb/points/PointConversion.h>

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

//openvdb::Vec3R


bool OpenVDBFileWriter::write(const std::string& filename) const
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
    //std::cout << grid->gridType() << std::endl;

    openvdb::io::File file(filename);
    /*
    if (!file.isOpen()) {
        return false;
    }
    */
    file.write({ grid });
    file.close();
    return true;
}
