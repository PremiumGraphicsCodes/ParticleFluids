#include "MacroParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

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
						preCount++;
					}
				}
			}
		}
	}
}

void MacroParticle::reset()
{
	this->microCount = 0;
	this->averagedCenter = Math::Vector3dd(0, 0, 0);
	this->averagedVelocity = Math::Vector3dd(0, 0, 0);
	this->force = Math::Vector3dd(0, 0, 0);
}


/*
void MacroParticle::calculateDensity()
{
	this->density = (innerPoints.size() - points.size()) / (double)points.size();
}
*/

void MacroParticle::addMicro(MicroParticle* microParticle)
{
	averagedCenter += microParticle->getPosition();
	averagedVelocity += microParticle->getVelocity();
	microCount++;
}

void MacroParticle::calculatePressure()
{
	if (isStatic) {
		return;
	}
	averagedCenter += position * (double)preCount;
	averagedCenter /= (double)(microCount + preCount);
	this->force += (this->position - averagedCenter) * 5000.0;
}

void MacroParticle::calculateViscosity()
{
	averagedVelocity += velocity * (double)preCount;
	averagedVelocity /= (double)(microCount + preCount);
	this->force -= (this->velocity - averagedVelocity) * 50.0;
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
	return microCount / (double)preCount;
}
