#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Algo::Physics;

void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;
	for (double x = -0.5 + tolerance; x < 0.5 - tolerance; x += dx) {
		for (double y = -0.5 + tolerance; y < 0.5 - tolerance; y += dy) {
//			for (double z = -0.5; z < 0.5 + tolerance; z += dy) {
				const Vector3dd v(Vector3dd(x, y, 0.0));
				if (Math::getLengthSquared(v) < 0.5 * 0.5) {
					points.push_back(new MicroParticle(this, v));
				}
			}
//		}
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
	this->force = this->velocity - averagedVelocity;
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