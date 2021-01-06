#pragma once

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
	}
	namespace VDB {
		class VDBParticleSystemScene;
		class VDBVolumeScene;

class VDBParticleSystemConverter
{
public:
	void toVolume(const VDBParticleSystemScene& particles, const float radius, VDBVolumeScene* volume);

	void fromVDB(const VDBParticleSystemScene& src, Scene::ParticleSystemScene* ps);

	//VDBParticleSystem toVDB(const Shape::IParticleSystem& src);

private:
};
	}
}