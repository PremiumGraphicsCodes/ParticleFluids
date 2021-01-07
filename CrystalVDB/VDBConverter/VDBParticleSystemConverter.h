#pragma once

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class IParticleSystemScene;
	}
	namespace VDB {
		class VDBParticleSystemScene;
		class VDBVolumeScene;

class VDBParticleSystemConverter
{
public:
	void toVolume(const VDBParticleSystemScene& particles, const float radius, VDBVolumeScene* volume);

	void fromVDB(const VDBParticleSystemScene& src, Scene::ParticleSystemScene* ps);

	void toVDB(const Scene::IParticleSystemScene& src, VDBParticleSystemScene* dest);

private:
};
	}
}