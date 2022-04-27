#include "MVPParticleBuilder.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "Crystal/Math/Gaussian3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

MVPVolumeParticle* Crystal::Physics::MVPParticleBuilder::create(const Math::Vector3df& position, const float radius, const float weight, const float temperature)
{
	auto vp = new MVPVolumeParticle(radius, position);
	auto mp = new MVPMassParticle(vp, Vector3dd(0,0,0), weight);
	vp->setRestMass(weight * 1.25f);
	vp->addMassParticle(mp);
	vp->setTemperature(temperature);
	mp->setParent(vp);
	//vp->addMassParticle(mp);
	return vp;
	//	restMass *= 1.5;
	//	selfMass = unum * vnum * wnum * weight;
}
