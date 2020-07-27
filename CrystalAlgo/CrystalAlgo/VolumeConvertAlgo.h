#pragma once

#include "../../Crystal/Shape/Volume.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace Algo {

class VolumeConvertAlgo
{
public:
	VolumeConvertAlgo(const Math::Box3d& box, const double divideLength);

	void add(Shape::IParticle* particle);

	void build(const double searchRadius);

private:
	Shape::Volume<double> volume;
	std::list<Shape::IParticle*> particles;
};
	}
}