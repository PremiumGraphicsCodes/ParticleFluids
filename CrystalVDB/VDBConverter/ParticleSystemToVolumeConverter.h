#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "VDBParticleSystem.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class ParticleSystemToVolumeConverter
{
public:
	std::unique_ptr<VDBVolume> toVolume(const VDBParticleSystem& particles, const float radius);

private:
};
	}
}