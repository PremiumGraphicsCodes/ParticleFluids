#include "OpenVDBFileWriter.h"

#include <openvdb/points/PointConversion.h>

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::OpenVDB;

//openvdb::Vec3R

namespace {
    openvdb::io::File file("");
}

OpenVDBFileWriter::~OpenVDBFileWriter()
{
    close();
}

bool OpenVDBFileWriter::open(const std::string& filePath)
{
    file = openvdb::io::File(filePath);
    return true;
}

void OpenVDBFileWriter::close()
{
    file.close();
}

void OpenVDBFileWriter::write(const std::string& name, const std::vector<Vector3dd>& positions) const
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

    /*
    if (!file.isOpen()) {
        return false;
    }
    */
    file.write({ grid });
}
