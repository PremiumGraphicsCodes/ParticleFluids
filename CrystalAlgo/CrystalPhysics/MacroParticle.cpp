#include "MacroParticle.h"

#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MacroParticle::MacroParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	selfCount(0)
{}

// MicroParticleを遠くに配置する->探索では自分に入らない．
void MacroParticle::distributePoints(const int unum, const int vnum)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;

	const auto r = 0.35;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			const auto xx = x / (double)unum;
			const auto yy = y / (double)vnum;
			const Vector3dd v(xx - 0.5, yy - 0.5, 0.0);
			const auto d = Math::getLengthSquared(v);
			if (d < 0.5 * 0.5) {
				points.push_back(new MicroParticle(this, v * 2.0, 1.0));
				selfCount++;
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

	const auto r = 0.35;
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			for (int z = 0; z <= wnum; ++z) {
				const auto xx = x / (double)unum;
				const auto yy = y / (double)vnum;
				const auto zz = z / (double)wnum;
				const Vector3dd v(xx - 0.5, yy - 0.5,  zz - 0.5);
				const auto d = Math::getLengthSquared(v);
				if (d < 0.5 * 0.5) {
					points.push_back(new MicroParticle(this, v * 2.0, 1.0));
					selfCount++;
				}
			}
		}
	}
}

void MacroParticle::reset(bool resetMicro)
{
	this->boundaryCount = 0;
	this->force = Math::Vector3dd(0, 0, 0);
	if (resetMicro) {
		this->microPoints.clear();
		this->microPoints.reserve(64);
	}
}


/*
void MacroParticle::calculateDensity()
{
	this->density = (innerPoints.size() - points.size()) / (double)points.size();
}
*/

void MacroParticle::addMicro(MicroParticle* microParticle)
{
	microPoints.push_back(microParticle);
	/*
	averagedCenter += microParticle->getPosition();
	averagedVelocity += microParticle->getVelocity();
	microCount++;
	*/
}

void MacroParticle::calculatePressure(const double pressureCoe)
{
	if (isStatic) {
		return;
	}
	Vector3dd averagedCenter(0, 0, 0);
	for (auto mp : microPoints) {
		averagedCenter += mp->getPosition() * mp->getWeight();
	}
	averagedCenter /= (double)(microPoints.size());
	const auto ratio = ((microPoints.size() + boundaryCount) / (double)selfCount) - 1.0;
	this->force += (this->position - averagedCenter) * ratio * pressureCoe;// 10000.0;
}

void MacroParticle::calculateViscosity(const double viscosityCoe)
{
	Vector3dd averagedVelocity(0, 0, 0);
	for (auto mp : microPoints) {
		averagedVelocity += mp->getVelocity() * mp->getWeight();
	}
	averagedVelocity /= (double)(microPoints.size());
	this->force -= (this->velocity - averagedVelocity) * viscosityCoe;//50.0;
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
	return (microPoints.size() + selfCount + boundaryCount) / (double)selfCount;
	//return microCount / (double)(microCount + preCount);
}

void MacroParticle::updateMicros()
{
	for (auto mp : this->microPoints) {
		mp->updatePosition();
	}
}
