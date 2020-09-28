#pragma once

#include "ParticleSystem.h"

namespace Crystal {
	namespace OpenVDB {

class ParticlesToVolumeConverter
{
public:
	openvdb::FloatGrid::Ptr toVolume(const ParticleSystem& particles);

private:
};
	}
}