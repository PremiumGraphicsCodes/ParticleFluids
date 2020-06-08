#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Algo::Physics;

void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;
	for (double x = 0.0; x <= 1.0 + tolerance; x += dx) {
		for (double y = 0.0; y < 1.0 + tolerance; y += dy) {
			const Vector3dd v(Vector3dd(x, y, 0.0));
			if (Math::getLengthSquared(v) > 0.5 * 0.5) {
				points.push_back(new MicroParticle(this, v));
			}
		}
	}
}

double MacroParticle::calculateDensity()
{
	return (innerPoints.size() - points.size()) / points.size();
}

void MacroParticle::calculatePressure()
{
	Vector3dd byCenter(0.0, 0.0, 0.0);
	for (const auto& ip : innerPoints) {
		byCenter += ip->getPosition();
	}
	byCenter /= (double)innerPoints.size();
	this->force += this->position - byCenter;
}

void MacroParticle::calculateViscosity()
{
	Vector3dd averagedVelocity(0.0, 0.0, 0.0);
	for (const auto& ip : innerPoints) {
		auto mp = static_cast<MicroParticle*>(ip);
		averagedVelocity += mp->getVelocity();
	}
	averagedVelocity /= (double)innerPoints.size();
	//byCenter /= (double)innerPoints.size();

}