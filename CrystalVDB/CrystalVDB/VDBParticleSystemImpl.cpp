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
    std::vector<openvdb::Vec3f> positions(size());
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        const auto& array = leafIter->constAttributeArray("P");
        openvdb::points::AttributeHandle<openvdb::Vec3f> positionHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            openvdb::Vec3f voxelPosition = positionHandle.get(*indexIter);
            const auto xyz = indexIter.getCoord().asVec3d();
            openvdb::Vec3f worldPosition = grid->transform().indexToWorld(voxelPosition + xyz);
            auto index = *indexIter;
            positions[index] = worldPosition;
        }
    }
    return positions;
}

std::vector<float> VDBParticleSystemImpl::getFloatAttributes(const std::string& name) const
{
    std::vector<float> values;
    values.resize(size());
    for (auto leafIter = grid->tree().cbeginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        const auto& array = leafIter->constAttributeArray(name);
        openvdb::points::AttributeHandle<float> floatHandle(array);
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            const auto index = *indexIter;
            const auto v = floatHandle.get(*indexIter);
            values[index] = v;
        }
    }
    return values;
}

void VDBParticleSystemImpl::setFloatAttributes(const std::string& name, const std::vector<float>& values)
{
    for (auto leafIter = grid->tree().beginLeaf(); leafIter; ++leafIter) {
        //std::cout << "Leaf" << leafIter->origin() << std::endl;
        // Extract the position attribute from the leaf by name (P is position).
        //const auto array = leafIter->attributeArray(name);
        openvdb::points::AttributeWriteHandle<float> floatHandle(leafIter->attributeArray(name));
        for (auto indexIter = leafIter->beginIndexOn(); indexIter; ++indexIter) {
            const auto index = *indexIter;
            floatHandle.set(*indexIter, values[index]);
        }
    }
}

/*
void VDBParticleSystemImpl::setValues(const std::vector<Particle>& particles)
{

}
*/

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
