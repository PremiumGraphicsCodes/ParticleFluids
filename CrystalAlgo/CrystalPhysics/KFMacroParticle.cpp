#include "KFMacroParticle.h"

#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

KFMacroParticle::KFMacroParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	selfMass(0.0f)
{}

KFMacroParticle::~KFMacroParticle()
{
	for (auto p : points) {
		delete p;
	}
	//points.clear();
}

// MicroParticleを遠くに配置する->探索では自分に入らない．
void KFMacroParticle::distributePoints(const int unum, const int vnum)
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
//				const auto weight = (1.0 - std::sqrt(d) * 2.0);
				points.push_back(new KFMicroParticle(this, v * 3.0, 1.0)); //weight));////d));
//				selfCount++;
			}
		}
	}
	//selfCount = unum * vnum;
}


void KFMacroParticle::distributePoints(const int unum, const int vnum, const int wnum, const float weight)
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
					points.push_back(new KFMicroParticle(this, v * 3.0, weight));
//					selfWeight+= weight;
				}
			}
		}
	}
	selfMass = unum * vnum * wnum * weight;
}

void KFMacroParticle::reset(bool resetMicro)
{
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

void KFMacroParticle::addMicro(KFMicroParticle* microParticle)
{
	microPoints.push_back(microParticle);
	/*
	averagedCenter += microParticle->getPosition();
	averagedVelocity += microParticle->getVelocity();
	microCount++;
	*/
}

void KFMacroParticle::calculatePressure(const float pressureCoe)
{
	Vector3df averagedCenter(0, 0, 0);
	for (auto mp : innerPoints) {
		averagedCenter += mp->position * mp->getMass();
	}
	averagedCenter /= totalMass;
	auto ratio = (totalMass / selfMass) - 1.0f;
	ratio = std::max(0.0f, ratio);
	this->force += (this->position - averagedCenter) * ratio * pressureCoe;// 10000.0;
}

void KFMacroParticle::calculateViscosity(const float viscosityCoe)
{
	Vector3df averagedVelocity(0, 0, 0);
	for (auto mp : innerPoints) {
		averagedVelocity += mp->getVelocity() * mp->getMass();
	}
	averagedVelocity /= totalMass;
	this->force -= (this->velocity - averagedVelocity) * viscosityCoe;//50.0;
}

void KFMacroParticle::stepTime(const float dt)
{
	const auto acc = (force) / 1.0f;//getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;
}

float KFMacroParticle::getDensity() const
{
	return totalMass / selfMass;
	//return microCount / (double)(microCount + preCount);
}

void KFMacroParticle::updateMicros()
{
	for (auto mp : this->microPoints) {
		mp->updatePosition();
	}
}

void KFMacroParticle::updateInnerPoints()
{
	const auto r = this->radius * 2.0;
	innerPoints.clear();
	totalMass = 0.0f;
	for (auto mp : this->microPoints) {
		const auto distanceSquared = Math::getDistanceSquared(mp->getPosition(), this->getPosition());
		if (distanceSquared < r * r) {
			innerPoints.push_back(mp);
			totalMass += mp->getMass();
		}
	}
}
