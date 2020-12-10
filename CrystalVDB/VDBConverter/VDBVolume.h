#pragma once

#include <memory>

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Shape {
		class IParticleSystem;
	}
	namespace VDB {
		class VolumeImpl;

class VDBVolume : private UnCopyable
{
public:
	VDBVolume();

	explicit VDBVolume(const float value);

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	~VDBVolume();

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	VolumeImpl* getImpl() const { return impl; }

	//Crystal::Shape::ParticleSystem* toCrystalParticleSystem();

private:
	VolumeImpl* impl;
};
	}
}