#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "VDBParticleSystemScene.h"
#include "VDBVolumeScene.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
	}
	namespace VDB {

class VDBParticleSystemConverter
{
public:
	std::unique_ptr<VDBVolumeScene> toVolume(const VDBParticleSystemScene& particles, const float radius);

	void fromVDB(const VDBParticleSystemScene& src, Scene::ParticleSystemScene* ps);

	//VDBParticleSystem toVDB(const Shape::IParticleSystem& src);

private:
};
	}
}