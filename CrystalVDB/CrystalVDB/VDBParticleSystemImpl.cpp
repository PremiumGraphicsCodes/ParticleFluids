#include "VDBParticleSystemImpl.h"

using namespace Crystal::VDB;

void VDBParticleSystemImpl::add(const openvdb::Vec3R& position, const openvdb::Real& radius, const openvdb::Vec3R& v)
{
    Particle pa;
    pa.position = position;
    pa.radius = radius;
    pa.velocity = v;
    particles.push_back(pa);
}

void VDBParticleSystemImpl::resize(const size_t count)
{
    this->particles.resize(count);
}

openvdb::CoordBBox VDBParticleSystemImpl::getBBox()
{
    openvdb::CoordBBox bbox;
    openvdb::Coord& min = bbox.min(), & max = bbox.max();
    openvdb::Vec3R pos;
    openvdb::Real rad, invDx = 1 / grid->voxelSize()[0];
    for (size_t n = 0, e = this->size(); n < e; ++n) {
        this->getPosRad(n, pos, rad);
        const openvdb::Vec3d xyz = grid->worldToIndex(pos);
        const openvdb::Real   r = rad * invDx;
        for (int i = 0; i < 3; ++i) {
            min[i] = openvdb::math::Min(min[i], openvdb::math::Floor(xyz[i] - r));
            max[i] = openvdb::math::Max(max[i], openvdb::math::Ceil(xyz[i] + r));
        }
    }
    return bbox;
}

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
