#include "KFMacroParticle.h"

#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

KFMacroParticle::KFMacroParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	selfCount(0)
{}

KFMacroParticle::~KFMacroParticle()
{
	for (auto p : points) {
		delete p;
	}
	//points.clear();
}

// MicroParticle�������ɔz�u����->�T���ł͎����ɓ���Ȃ��D
void KFMacroParticle::distributePoints(const int unum, const int vnum)
{
	// ���ォ��E���Ɍ������ċϓ���������D->���O���肷��D
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
				points.push_back(new MicroParticle(this, v * 3.0, 1.0)); //weight));////d));
//				selfCount++;
			}
		}
	}
	selfCount = unum * vnum;
}


void KFMacroParticle::distributePoints(const int unum, const int vnum, const int wnum)
{
	// ���ォ��E���Ɍ������ċϓ���������D->���O���肷��D
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
					points.push_back(new MicroParticle(this, v * 3.0, 1.0));
					selfCount++;
				}
			}
		}
	}
	selfCount = unum * vnum * wnum;
}

void KFMacroParticle::reset(bool resetMicro)
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

void KFMacroParticle::addMicro(MicroParticle* microParticle)
{
	microPoints.push_back(microParticle);
	/*
	averagedCenter += microParticle->getPosition();
	averagedVelocity += microParticle->getVelocity();
	microCount++;
	*/
}

void KFMacroParticle::calculatePressure(const double pressureCoe)
{
	if (isStatic) {
		return;
	}

	Vector3dd averagedCenter(0, 0, 0);
	for (auto mp : innerPoints) {
		averagedCenter += mp->getPosition() * mp->getWeight();
	}
	averagedCenter /= (double)(innerPoints.size());
	auto ratio = ((innerPoints.size() + boundaryCount) / (double)selfCount) - 1.0;
	ratio = std::max(0.0, ratio);
	this->force += (this->position - averagedCenter) * ratio * pressureCoe;// 10000.0;
}

void KFMacroParticle::calculateViscosity(const double viscosityCoe)
{
	Vector3dd averagedVelocity(0, 0, 0);
	for (auto mp : innerPoints) {
		averagedVelocity += mp->getVelocity() * mp->getWeight();
	}
	averagedVelocity /= (double)(innerPoints.size());
	this->force -= (this->velocity - averagedVelocity) * viscosityCoe;//50.0;
}

void KFMacroParticle::stepTime(const double dt)
{
	if (isStatic) {
		return;
	}
	const auto acc = (force) / getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;
}

double KFMacroParticle::getDensity() const
{
	return (microPoints.size() + boundaryCount) / (double)selfCount;
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
	for (auto mp : this->microPoints) {
		const auto distanceSquared = Math::getDistanceSquared(mp->getPosition(), this->getPosition());
		if (distanceSquared < r * r) {
			innerPoints.push_back(mp);
		}
	}
}