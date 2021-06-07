#include "MVPVolumeParticle.h"

#include "KFFluidScene.h"

#include "../SPHKernel.h"

#include "../../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

MVPVolumeParticle::MVPVolumeParticle(const float radius, const Vector3dd& position) :
	radius(radius),
	position(position),
	restMass(0.0f)
{}

MVPVolumeParticle::~MVPVolumeParticle()
{
	for (auto p : points) {
		delete p;
	}
	//points.clear();
}

void MVPVolumeParticle::distributePoints(const int unum, const int vnum, const int wnum, const float w)
{
	// 左上から右下に向かって均等分割する．->内外判定する．
	const auto dx = 1.0 / (double)unum;
	const auto dy = 1.0 / (double)vnum;

	const double tolerance = 1.0e-12;

	//SPHKernel kernel(0.5);
	Gaussian gaussian(0.0, 0.5);
	for (int x = 0; x <= unum; x++) {
		for (int y = 0; y <= vnum; ++y) {
			for (int z = 0; z <= wnum; ++z) {
				const auto xx = x / (double)unum;
				const auto yy = y / (double)vnum;
				const auto zz = z / (double)wnum;
				const Vector3dd v(xx - 0.5, yy - 0.5,  zz - 0.5);
				const auto d = Math::getLengthSquared(v);
				if (d < 0.5 * 0.5) {
//					const auto weight = (1.0 - std::sqrt(d) * 2.0);
//					const auto weight = kernel.getCubicSpline(std::sqrt(d)) * w;
					const auto weight = gaussian.getValue(d);
					auto p = new MVPMassParticle(this, v * 2.0, weight);
					points.push_back(p);
					restMass += weight;
				}
			}
		}
	}
	//selfMass *= 1.5;
//	selfMass = unum * vnum * wnum * weight;
}

void MVPVolumeParticle::setPressureCoe(const float c)
{
	for (auto p : points) {
		p->setPressureCoe(c);
	}
}

void MVPVolumeParticle::setViscosityCoe(const float c)
{
	for (auto p : points) {
		p->setViscosityCoe(c);
	}
}

void MVPVolumeParticle::reset(bool resetMicro)
{
	this->force = Math::Vector3dd(0, 0, 0);
	if (resetMicro) {
		this->microPoints.clear();
		this->microPoints.reserve(64);
	}
}

void MVPVolumeParticle::addMicro(MVPMassParticle* microParticle)
{
	microPoints.push_back(microParticle);
}

void MVPVolumeParticle::calculateDensity()
{
	float mass = 0.0f;
	for (auto m : innerPoints) {
		mass += m->getMass();
	}
	this->density = (mass / restMass);
}

void MVPVolumeParticle::calculatePressure()
{
	this->pressure = (density - 1.0f);
	this->pressure = std::max(0.0f, this->pressure);
	for (auto mp : microPoints) {
		mp->setPressure(this->pressure);
	}
}

void MVPVolumeParticle::calculatePressureForce(const float relaxationCoe)
{
	Math::Vector3df f(0, 0, 0);
	for (auto mp : innerPoints) {
		f += (this->pressure + mp->getPressure()) * (this->position - mp->position) * mp->getMass() * mp->getPressureCoe();
	}
	this->force += f;
}

void MVPVolumeParticle::calculateViscosityForce()
{
	Math::Vector3df f(0, 0, 0);
	for (auto mp : innerPoints) {
		f -= ( this->velocity - mp->getVelocity()) * mp->getMass() * mp->getViscosityCoe();
	}
	this->force += f;
}

void MVPVolumeParticle::calculateVorticity()
{
	vorticity = Vector3df(0, 0, 0);
	for (auto mp : innerPoints) {
		const auto p = (mp->position - this->position);
		const auto v = (mp->getVelocity() - this->velocity);
		vorticity += glm::cross(p, v);
	}
}

void MVPVolumeParticle::stepTime(const float dt)
{
	const auto acc = (force) / getDensity();
	this->velocity += acc * dt;
	this->position += this->velocity * dt;
}

float MVPVolumeParticle::getDensity() const
{
	return this->density;
}

void MVPVolumeParticle::updateMicros()
{
	for (auto mp : this->microPoints) {
		mp->updatePosition();
	}
}

void MVPVolumeParticle::updateInnerPoints()
{
	const auto r = this->radius;
	innerPoints.clear();
	for (auto mp : this->microPoints) {
		const auto distanceSquared = Math::getDistanceSquared(mp->getPosition(), this->getPosition());
		if (distanceSquared < r * r) {
			innerPoints.push_back(mp);
		}
	}
}
