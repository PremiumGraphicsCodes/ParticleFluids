#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Algo::Physics;

MacroParticle::MacroParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	preCount(0)
{}

// MicroParticleを遠くに配置する->探索では自分に入らない．
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
			const Vector3dd v(xx - 0.5, yy - 0.5, 0.0);
			const auto length2 = Math::getLengthSquared(v);
			if (length2 < r * r) {
				if (length2 < 0.4 * 0.4) {
					preCount++;
				}
				else {
					points.push_back(new MicroParticle(this, v));
					preCount++;
				}
			}
		}
	}
}


void MacroParticle::distributePoints(const int unum, const int vnum, const int wnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;

	const auto r = 0.5;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			for (int z = 0; z <= wnum; ++z) {
				const auto xx = x / (double)unum;
				const auto yy = y / (double)vnum;
				const auto zz = z / (double)wnum;
				const Vector3dd v(xx - 0.5, yy - 0.5,  zz - 0.5);
				const auto length2 = Math::getLengthSquared(v);
				if (length2 < r * r) {
					if (length2 < 0.4 * 0.4) {
						preCount++;
					}
					else {
						points.push_back(new MicroParticle(this, v));
					}
				}
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
	this->force += (this->position - byCenter) * 5000.0;
}

void MacroParticle::calculateViscosity()
{
	Vector3dd averagedVelocity(0.0, 0.0, 0.0);
	const auto count = (double)(innerPoints.size() + preCount);
	for (const auto& ip : innerPoints) {
		auto mp = static_cast<MicroParticle*>(ip);
		averagedVelocity += mp->getVelocity();
	}
	averagedVelocity += (double)preCount * getVelocity();
	averagedVelocity /= (double)count;
	this->force -= (this->velocity - averagedVelocity) * 50.0;
	//byCenter /= (double)innerPoints.size();

}

void MacroParticle::stepTime(const double dt)
{
	if (isStatic) {
		return;
	}
	const auto acc = (force) / getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;
}

double MacroParticle::getDensity() const
{
	return (innerPoints.size() + preCount) / (double)preCount;
}
