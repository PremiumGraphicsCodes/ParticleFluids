#pragma once

#include <memory>

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
	}
	namespace VDB {
		class VolumeImpl;

class Volume : private UnCopyable
{
public:
	Volume();

	explicit Volume(const float value);

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	~Volume();

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	VolumeImpl* getImpl() const { return impl; }

	//Crystal::Scene::ParticleSystemScene* toCrystalParticleSystem();

private:
	VolumeImpl* impl;
};
	}
}