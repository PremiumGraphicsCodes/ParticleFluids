#include "MVPSampler.h"

#include "MVP/MVPFluidScene.h"
#include "CrystalSpace/CrystalSpace/CompactSpaceHash3d.h"
#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPSampler::split(const std::list<MVPFluidScene*>& fluids)
{
	for (auto f : fluids) {
		const auto fps = f->getParticles();
		std::vector<MVPVolumeParticle*> ps;
		for (auto p : fps) {
			if (p->getDensity() < 0.75) {
				ps.push_back(p);
			}
		}
		for (auto p : ps) {
			const auto masses = p->getMassParticles();
			for (auto m : masses) {
				MVPVolumeParticle* vp = new MVPVolumeParticle(p->getRadius() * 0.50, m->getPosition());
				vp->setVelocity(m->getVelocity());
				vp->addMassParticle(m);
				m->setParent(vp);
				vp->setRestMass(m->getMass());
				f->add(vp);
			}
			p->clearMasses();
		}
	}

	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}
}

void MVPSampler::merge(const std::list<MVPFluidScene*>& fluids, const double searchRadius)
{
	std::list<MVPVolumeParticle*> tinyParticles;
	for (auto f : fluids) {
		const auto fps = f->getParticles();
		for (auto p : fps) {
			if (p->getMassParticles().size() == 1) {
				tinyParticles.push_back(p);
			}
		}
	}
	CompactSpaceHash3d spaceHash2(searchRadius * 0.5, tinyParticles.size());
	for (auto p : tinyParticles) {
		spaceHash2.add(p);
	}
	for (auto p : tinyParticles) {
		const auto neighbors = spaceHash2.findNeighbors(p);
		if (neighbors.size() >= 7) {
			std::cout << "IsAbleToMerge" << std::endl;
			auto target = static_cast<MVPVolumeParticle*>(p);
			Vector3df newPosition = target->getPositionf();
			Vector3df newVelocity = target->getVelocity();
			for (int i = 0; i < 7; ++i) {
				auto n = static_cast<MVPVolumeParticle*>(neighbors[i]);
				auto m = n->getMassParticles().front();
				target->addMassParticle(m);
				m->setParent(target);
				n->clearMasses();
				newPosition += n->getPositionf();
				newVelocity += n->getVelocity();
			}
			target->setRadius(target->getRadius() * 2.0);
			newPosition /= 8.0f;
			target->setPosition(newPosition);
			newVelocity /= 8.0f;
			target->setVelocity(newVelocity);
			break;
		}
	}
	for (auto f : fluids) {
		f->removeDegeneratedVolumes();
	}

}