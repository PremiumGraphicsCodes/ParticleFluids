#include "MVPParticleBuilder.h"

#include "MVPMassParticle.h"
#include "MVPVolumeParticle.h"

#include "../../../Crystal/Math/Gaussian3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

MVPVolumeParticle* Crystal::Physics::MVPParticleBuilder::create(const Math::Vector3df& position, const float radius, const int unum, const int vnum, const int wnum, const float weight)
{
	MVPVolumeParticle* volume = new MVPVolumeParticle(radius, position);

	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	float restMass = 0.0f;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			for (int z = 0; z <= wnum; ++z) {
				const auto xx = x / (double)unum;
				const auto yy = y / (double)vnum;
				const auto zz = z / (double)wnum;
				const Vector3dd v(xx - 0.5, yy - 0.5, zz - 0.5);
				const auto d = Math::getLengthSquared(v);
				if (d < 0.5 * 0.5) {
					auto mp = new MVPMassParticle(volume, v, weight / 8.0f);
					volume->addMassParticle(mp);
					restMass += weight / 8.0f;
				}
			}
		}
	}
	restMass *= 1.5;
	volume->setRestMass(restMass);
	return volume;
	//	restMass *= 1.5;
	//	selfMass = unum * vnum * wnum * weight;
}
