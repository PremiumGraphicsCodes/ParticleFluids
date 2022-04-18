#pragma once

#include "openvdb/openvdb.h"
#include "openvdb/points/PointConversion.h"

namespace Crystal {
    namespace VDB {

struct Particle
{
    openvdb::Vec3R position;
    openvdb::Real  radius;
};

class VDBParticleSystemImpl
{
protected:
    openvdb::Real           mRadiusScale;
    std::vector<Particle> particles;
public:
    typedef openvdb::Vec3R  PosType;

    VDBParticleSystemImpl(openvdb::Real rScale = 1)
        : mRadiusScale(rScale) {}

    ~VDBParticleSystemImpl()
    {}

    //void add(const openvdb::Vec3R& position, const openvdb::Real& radius);

    void resize(const size_t count);

    //typedef int AttributeType;
    // The methods below are only required for the unit-tests
    openvdb::Vec3R pos(int n) const { return particles[n].position; }

    openvdb::Real radius(int n) const { return mRadiusScale * particles[n].radius; }

    //////////////////////////////////////////////////////////////////////////////
    /// The methods below are the only ones required by tools::ParticleToLevelSet
    /// @note We return by value since the radius and velocities are modified
    /// by the scaling factors! Also these methods are all assumed to
    /// be thread-safe.

    /// Return the total number of particles in list.
    ///  Always required!
    size_t size() const { return particles.size(); }

    /// Get the world space position of n'th particle.
    /// Required by ParticledToLevelSet::rasterizeSphere(*this,radius).
    void getPos(size_t n, openvdb::Vec3R& pos) const { pos = particles[n].position; }

    void getPosRad(size_t n, openvdb::Vec3R& pos, openvdb::Real& rad) const {
        pos = particles[n].position;
        rad = mRadiusScale * particles[n].radius;
    }

    // The method below is only required for attribute transfer
    void getAtt(size_t n, openvdb::Index32& att) const { att = openvdb::Index32(n); }

    void addFloatAttribute(const std::string& name);

    std::vector<openvdb::Vec3f> getPositions() const;

    std::vector<float> getFloatAttributes(const std::string& name) const;

    std::vector<std::string> getAttributeNames() const;

    bool hasAttribute(const std::string& name) const;

    void setPtr(openvdb::points::PointDataGrid::Ptr grid) { this->grid = grid; }

    openvdb::points::PointDataGrid::Ptr getPtr() { return grid; }

private:
    openvdb::points::PointDataGrid::Ptr grid;
};
    }
}
