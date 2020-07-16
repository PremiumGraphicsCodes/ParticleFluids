#include "DFFluidSolver.h"
#include "DFSPHParticle.h"
#include "DFFluidScene.h"

#include "../CrystalAlgo/CompactSpaceHash3d.h"

#include "../CrystalAlgo/IndexedSortSearchAlgo.h"
//#include "PBSPHBoundarySolver.h"

using namespace Crystal::Math;
using namespace Crystal::Search;
using namespace Crystal::Physics;

DFFluidSolver::DFFluidSolver() :
	maxTimeStep(0.01)
{}

void DFFluidSolver::step()
{
	simulate(maxTimeStep, 2.25, 2.5, 3);
}

void DFFluidSolver::simulate(const float dt, const float effectLength, const float searchLength, const int maxIter)
{
	std::vector<DFSPHParticle*> particles;
	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		particles.insert(particles.end(), ps.begin(), ps.end());
	}

	/*
	for (auto p : particles) {
		p->init();
	}
	*/

	const auto hashSize = static_cast<int>(particles.size()) * 2;
	const auto searchRadius = particles.front()->getRadius() * 2.25;
	CompactSpaceHash3d spaceHash(searchRadius, hashSize);
	for (auto particle : particles) {
		spaceHash.add(particle);
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		auto particle = particles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto mp : neighbors) {
			particle->addNeighbor(static_cast<DFSPHParticle*>(mp));
		}
	}

#pragma omp parallel for
	for (int i = 0; i < particles.size(); ++i) {
		particles[i]->calculateDensity();
		particles[i]->calculateAlpha();
	}

	// compute factor alpha.

	auto time = 0.0;
	while (time < maxTimeStep) {
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->force += Vector3dd(0.0, -9.8, 0.0) * particles[i]->getMass();
		}

		const auto dt = calculateTimeStep(particles);

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->velocity += dt * particles[i]->force / particles[i]->getMass();
		}
		correctDensityError(particles);

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->position += dt * particles[i]->getVelocity();
		}

		spaceHash.clear();
		for (int i = 0; i < particles.size(); ++i) {
			spaceHash.add(particles[i]);
		}

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			auto particle = particles[i];
			const auto& neighbors = spaceHash.findNeighbors(particle);
			for (auto mp : neighbors) {
				particle->addNeighbor(static_cast<DFSPHParticle*>(mp));
			}
		}

#pragma omp parallel for
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateDensity();
			particles[i]->calculateAlpha();
		}

		correctDivergenceError(particles);
	}
}

void DFFluidSolver::correctDivergenceError(const std::vector<DFSPHParticle*>& particles)
{
	int iter = 0;
	while (iter < 1) {

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateDpDt();
		}

		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateVelocityInDivergenceError();
		}
	}
}

void DFFluidSolver::correctDensityError(const std::vector<DFSPHParticle*>& particles)
{
	int iter = 0;
	while (iter < 2) {
		for (int i = 0; i < particles.size(); ++i) {

			// predict density
			//particles[i]->dp();
		}
		for (int i = 0; i < particles.size(); ++i) {
			particles[i]->calculateVelocityInDensityError();
		}
	}
}

double DFFluidSolver::calculateTimeStep(const std::vector<DFSPHParticle*>& particles)
{
	double maxVelocity = 0.0;
	for (auto p : particles) {
		maxVelocity = std::max<double>(maxVelocity, Math::getLengthSquared(p->getVelocity()));
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4 * particles.front()->getRadius() * 2.0 / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}