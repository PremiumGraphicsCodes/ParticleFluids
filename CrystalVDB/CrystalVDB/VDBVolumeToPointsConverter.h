#pragma once

namespace Crystal {
	namespace VDB {
		class VDBVolumeScene;
		class VDBParticleSystemScene;

class VDBVolumeToPointsConverter
{
public:
	static VDBParticleSystemScene* toPoints(const VDBVolumeScene& volume);

private:
};

	}
}