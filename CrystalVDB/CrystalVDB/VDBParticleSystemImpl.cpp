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