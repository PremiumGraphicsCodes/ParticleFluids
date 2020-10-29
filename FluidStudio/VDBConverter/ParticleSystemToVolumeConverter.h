#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "ParticleSystem.h"
#include "Volume.h"

namespace Crystal {
	namespace VDB {

class ParticleSystemToVolumeConverter
{
public:
	std::unique_ptr<Volume> toVolume(const ParticleSystem& particles);

private:
};
	}
}