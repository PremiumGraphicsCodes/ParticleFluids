#include "VDBFileReader.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

#include "VDBVolumeImpl.h"
#include "VDBParticleSystemScene.h"
#include "VDBVolumeScene.h"

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

VDBParticleSystemScene* VDBFileReader::readPositions(const std::string& pointName, const float radius)
{
    auto baseGrid = file.readGrid(pointName);

    auto grid = openvdb::gridPtrCast<openvdb::points::PointDataGrid>(baseGrid);
    auto count = openvdb::points::pointCount(grid->tree());
    //std::cout << "PointCount=" << count << std::endl;

    std::vector<openvdb::Vec3R> v_positions;
    std::vector<openvdb::Index32> v_indices;

    VDBParticleSystemScene* psScene = new VDBParticleSystemScene();

    //using Codec = openvdb::points::FixedPointCodec</*1-byte=*/false,
    //    openvdb::points::UnitRange>;
    //openvdb::points::TypedAttributeArray<float, Codec>::registerType();
    //openvdb::NamePair radiusAttribute =
    //    openvdb::points::TypedAttributeArray<float, Codec>::attributeType();
    //openvdb::points::appendAttribute(grid->tree(), "pscale", radiusAttribute);

    //const auto desc = grid->tree().cbeginLeaf()->attributeSet().descriptor();
    //const auto attrs = grid->tree().cbeginLeaf()->attributeSet();
    //const auto map = desc.map();
    //for (int i = 0; i < desc.size(); ++i) {
    //    const auto type = attrs.get(i)->type();
    //}

    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray("P");
//        leafIter->hasAttribute("pscale");
//        const auto& radiusArray = leafIter->constAttributeArray("pscale");

        // Create a read-only AttributeHandle. Position always uses Vec3f.
        openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
  //      openvdb::points::AttributeHandle<float> radiusHandle(radiusArray);

        // Iterate over the point indices in the leaf.
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
//            const auto radius = radiusHandle.get(*indexIter);
            const auto xyz = indexIter.getCoord().asVec3d();
            openvdb::Vec3f worldPosition = grid->transform().indexToWorld(voxelPosition + xyz);
//            v_positions.push_back(worldPosition);
            auto index = *indexIter;
            v_indices.push_back(index);
            psScene->add(Converter::fromVDB(worldPosition), radius);
        }
    }

    return psScene;
}

VDBVolumeScene* VDBFileReader::readVolume(const std::string& volumeName)
{
    auto grid = openvdb::gridPtrCast<openvdb::FloatGrid>( file.readGrid(volumeName) );
    //auto impl = new VDBVolumeImpl( grid );
    auto scene = new VDBVolumeScene();
    scene->getImpl()->setPtr(grid);
    return scene;
}