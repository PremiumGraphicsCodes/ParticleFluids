#include "VDBFileReader.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

#include "VDBVolumeImpl.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

namespace {
    openvdb::io::File file("");
}

VDBFileReader::~VDBFileReader()
{
    if (file.isOpen()) {
        close();
    }
}

bool VDBFileReader::open(const std::string& filename)
{
    file = openvdb::io::File(filename);
    const auto isOk = file.open();
    return isOk;
}

void VDBFileReader::close()
{
    file.close();
}

void VDBFileReader::readMetaData()
{
    auto metas = file.readAllGridMetadata();
    for (auto iter = metas->begin(); iter != metas->end(); ++iter) {
        const auto isPoint = (*iter)->isType<openvdb::points::PointDataGrid>();
        if (isPoint) {
            //std::cout << (*iter)->getName() << std::endl;
            pointNames.push_back((*iter)->getName());
            continue;
        }
        const auto isVolume = (*iter)->isType<openvdb::FloatGrid>();
        if (isVolume) {
            floatGridNames.push_back((*iter)->getName());
        }
    }
}

std::vector<Vector3dd> VDBFileReader::readPositions(const std::string& pointName)
{
    auto baseGrid = file.readGrid(pointName);

    auto grid = openvdb::gridPtrCast<openvdb::points::PointDataGrid>(baseGrid);
    auto count = openvdb::points::pointCount(grid->tree());
    //std::cout << "PointCount=" << count << std::endl;

    std::vector<openvdb::Vec3R> v_positions;
    std::vector<openvdb::Index32> v_indices;

    std::vector<Vector3dd> positions;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray("P");

        // Create a read-only AttributeHandle. Position always uses Vec3f.
        openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
        // Iterate over the point indices in the leaf.
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
            const auto xyz = indexIter.getCoord().asVec3d();
            openvdb::Vec3f worldPosition =
                grid->transform().indexToWorld(voxelPosition + xyz);
//            v_positions.push_back(worldPosition);
            auto index = *indexIter;
            v_indices.push_back(index);

            positions.push_back(Converter::fromVDB(worldPosition));
        }
    }

    return positions;
}

VDBVolumeImpl VDBFileReader::readVolume(const std::string& volumeName)
{
    auto grid = openvdb::gridPtrCast<openvdb::FloatGrid>( file.readGrid(volumeName) );
    return VDBVolumeImpl( grid );
}
