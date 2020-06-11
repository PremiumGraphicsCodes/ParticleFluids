#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Algo::Physics;

MacroParticle::MacroParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	preCount(0)
{}

void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;
	const auto r = 0.5;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			const auto xx = x / (double)unum;
			const auto yy = y / (double)vnum;
			const Vector3dd v(xx-r, yy-r, 0.0);
			const auto length2 = Math::getLengthSquared(v);
			if (length2 < r * r) {
				/*
				if (length2 < 0.5 * 0.5) {
					preCount++;
				}
				else {
				*/
					points.push_back(new MicroParticle(this, v));
				//}
			}
		}
	}
}

/*
void MacroParticle::calculateDensity()
{
	this->density = (innerPoints.size() - points.size()) / (double)points.size();
}
*/

void MacroParticle::calculatePressure()
{
	if (isStatic) {
		return;
	}
	Vector3dd byCenter(0.0, 0.0, 0.0);
	const auto count = (double)(innerPoints.size() + preCount);
	for (const auto& ip : innerPoints) {
		byCenter += ip->getPosition();
	}
	byCenter += (double)preCount * getPosition();
	byCenter /= (double)count;
	this->force += (this->position - byCenter) * 100.0;
}

void MacroParticle::calculateViscosity()
{
	Vector3dd averagedVelocity(0.0, 0.0, 0.0);
	for (const auto& ip : innerPoints) {
		auto mp = static_cast<MicroParticle*>(ip);
		averagedVelocity += mp->getVelocity();
	}
	averagedVelocity /= (double)innerPoints.size();
	this->force += (this->velocity - averagedVelocity) * 10.0;
	//byCenter /= (double)innerPoints.size();

}

void MacroParticle::stepTime(const double dt)
{
	if (isStatic) {
		return;
	}
	this->velocity += (force) * dt;
	this->position += this->velocity * dt;
}