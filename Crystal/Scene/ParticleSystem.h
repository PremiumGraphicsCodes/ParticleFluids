#pragma once

#include "../Shape/IShape.h"

#include "Particle.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

template<typename Attr>
class ParticleSystem
{
public:
	ParticleSystem() {}

	~ParticleSystem() {
		clear();
	}

	void clear() {
		for (auto p : particles) {
			delete p;
		}
		particles.clear();
	}
	
	void add(const Math::Vector3dd& position, const Attr& attr) {
		particles.push_back(new Particle<Attr>(position, attr));
	}

	void move(const Math::Vector3dd& v) {
		for (auto p : particles) {
			p->move(v);
		}
	}

	void transform(const Math::Matrix3dd& m) {
		for (auto p : particles) {
			p->transform(m);
		}
	}

	void transform(const Math::Matrix4dd& m) {
		for (auto p : particles) {
			p->transform(m);
		}
	}

	std::vector<Particle<Attr>*> getParticles() const { return particles; }

	std::vector<IParticle*> getIParticles() const
	{
		std::vector<IParticle*> ps;
		for (auto p : particles) {
			ps.push_back(p);
		}
		return ps;
	}

	Math::Box3d getBoundingBox() const
	{
		if (particles.empty()) {
			return Math::Box3d();
		}
		Math::Box3d bb(particles.front()->getPosition());
		for (auto p : particles) {
			bb.add(p->getPosition());
		}
		return bb;
	}

private:
	std::vector<Particle<Attr>*> particles;
};

	}
}
