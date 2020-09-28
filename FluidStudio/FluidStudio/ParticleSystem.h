#pragma once

#include "openvdb/openvdb.h"
#include <vector>

namespace Crystal {
    namespace OpenVDB {

        struct Particle
        {
            openvdb::Vec3R position;
            openvdb::Vec3R velocity;
            openvdb::Real  radius;
        };

        class ParticleSystem
        {
        protected:
            openvdb::Real           mRadiusScale;
            openvdb::Real           mVelocityScale;
            std::vector<Particle> particles;
        public:
            typedef openvdb::Vec3R  PosType;

            ParticleSystem(openvdb::Real rScale = 1, openvdb::Real vScale = 1)
                : mRadiusScale(rScale), mVelocityScale(vScale) {}

            void add(const openvdb::Vec3R& position, const openvdb::Real& radius, const openvdb::Vec3R& v = openvdb::Vec3R(0, 0, 0));

            /// @return coordinate bbox in the space of the specified transfrom
            openvdb::CoordBBox getBBox(const openvdb::GridBase& grid);

            //typedef int AttributeType;
            // The methods below are only required for the unit-tests
            openvdb::Vec3R pos(int n) const { return particles[n].position; }

            openvdb::Vec3R vel(int n)   const { return mVelocityScale * particles[n].velocity; }

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

            void getPosRadVel(size_t n, openvdb::Vec3R& pos, openvdb::Real& rad, openvdb::Vec3R& vel) const {
                pos = particles[n].position;
                rad = mRadiusScale * particles[n].radius;
                vel = mVelocityScale * particles[n].velocity;
            }

            // The method below is only required for attribute transfer
            void getAtt(size_t n, openvdb::Index32& att) const { att = openvdb::Index32(n); }
        };

    }
}