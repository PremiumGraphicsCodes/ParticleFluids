#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "ParticleSystem.h"

namespace Crystal {
	namespace OpenVDB {

class ParticlesToVolumeConverter
{
public:
	void add(const Math::Vector3dd& position);

	openvdb::FloatGrid::Ptr toVolume(const ParticleSystem& particles);

private:
};
	}
}