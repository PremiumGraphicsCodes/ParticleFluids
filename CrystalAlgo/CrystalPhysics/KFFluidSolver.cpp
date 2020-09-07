#include "KFFluidSolver.h"

#include "KFMacroParticle.h"
#include "KFMicroParticle.h"

#include "KFFluidScene.h"
#include "KFFBoundarySolver.h"
#include "../CrystalAlgo/CompactSpaceHash3d.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Search;
using namespace Crystal::Physics;

KFFluidSolver::KFFluidSolver() :
	maxTimeStep(0.03)
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
		if (particle->isStatic_()) {
			continue;
		}
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addMicro(static_cast<KFMicroParticle*>(n));
		}
	}

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(particles);

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			const auto particle = particles[i];
			particle->updateInnerPoints();
			particle->calculatePressure(particle->getScene()->getPressureCoe());
			particle->calculateViscosity(particle->getScene()->getViscosityCoe());
		}
		

		KFFBoundarySolver boundarySolver;
		boundarySolver.add(boundary);
		for (auto particle : particles) {
			//boundarySolver.createMacro(particle);
			boundarySolver.solve(particle, dt);
		}

		for (auto particle : particles) {
			particle->addForce(Vector3dd(0.0, -9.8 * particle->getDensity(), 0.0));
			particle->stepTime(dt);
		}

		// solve incompressibility.
		double relaxationCoe = 0.5;
		for (int i = 0; i < 2; ++i) {
			for (auto particle : particles) {
				particle->reset(false);
				particle->updateMicros();
			}

#pragma omp parallel for
			for (int i = 0; i < particles.size(); ++i) {
				const auto particle = particles[i];
				if (particle->isStatic_()) {
					continue;
				}
				particle->updateInnerPoints();
				particle->calculatePressure(particle->getScene()->getPressureCoe() * relaxationCoe);
			}

			for (auto particle : particles) {
				boundarySolver.solve(particle, dt);
			}
			//	solveBoundary(particles);

			for (auto particle : particles) {
				//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
				particle->stepTime(dt);
			}
			relaxationCoe /= 2.0;
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : particles) {
		densityError += particle->getDensity() / (double)particles.size();
	}
	std::cout << densityError << std::endl;


	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
	}
}

double KFFluidSolver::calculateTimeStep(const std::vector<KFMacroParticle*>& particles)
{
	double maxVelocity = 0.0;
	for (auto p : particles) {
		maxVelocity = std::max<double>(maxVelocity, Math::getLengthSquared( p->getVelocity() ) );
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4 * particles.front()->getRadius() * 2.0 / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}