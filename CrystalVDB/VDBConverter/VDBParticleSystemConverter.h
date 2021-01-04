#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "VDBParticleSystem.h"
#include "VDBVolume.h"

namespace Crystal {
	namespace Shape {
		class IParticleSystem;
	}
	namespace VDB {

class VDBParticleSystemConverter
{
public:
	std::unique_ptr<VDBVolume> toVolume(const VDBParticleSystem& particles, const float radius);

	std::unique_ptr<Shape::IParticleSystem> fromVDB(const VDBParticleSystem& src);

	//VDBParticleSystem toVDB(const Shape::IParticleSystem& src);

private:
};
	}
}