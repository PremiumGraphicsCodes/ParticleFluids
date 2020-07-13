#include "KFFluidSolver.h"

#include "MicroParticle.h"
#include "KFMacroParticle.h"

#include "KFFluidScene.h"
#include "KFFBoundarySolver.h"
#include "../CrystalAlgo/CompactSpaceHash3d.h"

using namespace Crystal::Math;
using namespace Crystal::Search;
using namespace Crystal::Physics;

KFFluidSolver::KFFluidSolver() :
	dt(0.03)
{}

void KFFluidSolver::step()
{
	simulate();
}

void KFFluidSolver::simulate()
{
	std::vector<KFMacroParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	for (auto particle : particles) {
		particle->reset(true);
	}

	const auto hashSize = particles.front()->getPoints().size() * particles.size();
	const auto searchRadius = particles.front()->getRadius() * 2.25;
	CompactSpaceHash3d spaceHash(searchRadius, hashSize);
	for (auto particle : particles) {
		particle->updateMicros();
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.add(mp);
		}
	}

#pragma omp parallel for
	for(int i = 0; i < particles.size(); ++i) {
		const auto particle = particles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addMicro(static_cast<MicroParticle*>(n));
		}
	}

	for (auto particle : particles) {
		particle->updateInnerPoints();
	}

	for (auto particle : particles) {
		particle->calculatePressure(particle->getScene()->getPressureCoe());
	}

	for (auto particle : particles) {
		particle->calculateViscosity(particle->getScene()->getViscosityCoe());
	}

	KFFBoundarySolver boundarySolver(boundary);
	for (auto particle : particles) {
		//boundarySolver.createMacro(particle);
		boundarySolver.solve(particle, dt);
	}

	for (auto particle : particles) {
		particle->addForce(Vector3dd(0.0,-9.8 * particle->getDensity(),0.0));
		particle->stepTime(dt);
	}

	// solve incompressibility.
	double relaxationCoe = 0.5;
	for (int i = 0; i < 2; ++i) {
		for (auto particle : particles) {
			particle->reset(false);
			particle->updateMicros();
		}

		for (auto particle : particles) {
			particle->updateInnerPoints();
		}

		for (auto particle : particles) {
			particle->calculatePressure(particle->getScene()->getPressureCoe() * relaxationCoe);
		}

		for (auto particle : particles) {
			boundarySolver.solve(particle, dt);
		}
	//	solveBoundary(particles);

		for(auto particle : particles) {
			//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
			particle->stepTime(dt);
		}
		relaxationCoe /= 2.0;
	}

	for (auto fluid : fluids) {
		fluid->getController()->updateView();
	}
}
