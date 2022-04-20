#include "VDBParticleSystemImpl.h"

using namespace Crystal::VDB;

void VDBParticleSystemImpl::addFloatAttribute(const std::string& name)
{
    using Codec = openvdb::points::FixedPointCodec</*1-byte=*/false,openvdb::points::UnitRange>;
    openvdb::points::TypedAttributeArray<float, Codec>::registerType();
    openvdb::NamePair radiusAttribute = openvdb::points::TypedAttributeArray<float, Codec>::attributeType();
    openvdb::points::appendAttribute(grid->tree(), name, radiusAttribute);
}

std::vector<openvdb::Vec3f> VDBParticleSystemImpl::getPositions() const
{
    std::vector<openvdb::Index32> v_indices;
    std::vector<openvdb::Vec3f> positions;
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
            positions.push_back(worldPosition);
            //psScene->add(Converter::fromVDB(worldPosition), radius);
        }
    }
    return positions;
}

std::vector<float> VDBParticleSystemImpl::getFloatAttributes(const std::string& name) const
{
    std::vector<openvdb::Index32> v_indices;
    std::vector<float> values;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray(name);
        openvdb::points::AttributeHandle<float> floatHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            float v = floatHandle.get(*indexIter);
            values.push_back(v);
            auto index = *indexIter;
            v_indices.push_back(index);
            //psScene->add(Converter::fromVDB(worldPosition), radius);
        }
    }
    return values;
}

void VDBParticleSystemImpl::setFloatAttributes(const std::string& name, const std::vector<float>& values) const
{
    std::vector<openvdb::Index32> v_indices;
    int index = 0;
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        auto array = leafIter->attributeArray(name);
        openvdb::points::AttributeWriteHandle<float> floatHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            floatHandle.set(*indexIter, values[index]);
            index++;
        }
    }
}

std::vector<std::string> VDBParticleSystemImpl::getAttributeNames() const
{
    const auto desc = grid->tree().cbeginLeaf()->attributeSet().descriptor();
    const auto attrs = grid->tree().cbeginLeaf()->attributeSet();
    const auto map = desc.map();
    std::vector<std::string> names;
    for (auto m : map) {
        names.push_back(m.first);
    }
    /*
    for (int i = 0; i < desc.size(); ++i) {
        const auto type = attrs.get(i)->type();
    }
    */
    return names;
}

bool VDBParticleSystemImpl::hasAttribute(const std::string& name) const
{
    const auto desc = grid->tree().cbeginLeaf()->attributeSet().descriptor();
    const auto map = desc.map();
    return map.find(name) != map.end();
}
