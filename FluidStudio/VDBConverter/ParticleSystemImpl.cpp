#include "ParticleSystemImpl.h"

using namespace Crystal::VDB;

void ParticleSystemImpl::add(const openvdb::Vec3R& position, const openvdb::Real& radius, const openvdb::Vec3R& v)
{
    Particle pa;
    pa.position = position;
    pa.radius = radius;
    pa.velocity = v;
    particles.push_back(pa);
}

openvdb::CoordBBox ParticleSystemImpl::getBBox(const openvdb::GridBase& grid)
{
    openvdb::CoordBBox bbox;
    openvdb::Coord& min = bbox.min(), & max = bbox.max();
    openvdb::Vec3R pos;
    openvdb::Real rad, invDx = 1 / grid.voxelSize()[0];
    for (size_t n = 0, e = this->size(); n < e; ++n) {
        this->getPosRad(n, pos, rad);
        const openvdb::Vec3d xyz = grid.worldToIndex(pos);
        const openvdb::Real   r = rad * invDx;
        for (int i = 0; i < 3; ++i) {
            min[i] = openvdb::math::Min(min[i], openvdb::math::Floor(xyz[i] - r));
            max[i] = openvdb::math::Max(max[i], openvdb::math::Ceil(xyz[i] + r));
        }
    }
    return bbox;
}
