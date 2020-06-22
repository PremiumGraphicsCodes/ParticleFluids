#include "CSPHSolver.h"
#include "CSPHParticle.h"
#include "CSPHBoundarySolver.h"

#include "../CrystalAlgo/IndexedFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;
using namespace Crystal::Physics;

void CSPHSolver::clear()
{
	timeStep = 0;
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

void CSPHSolver::step()
{
	simulate(1.25f);
}

void CSPHSolver::simulate(const float timeStep)
{
	this->timeStep++;

	for (auto particle : particles) {
		particle->init();
	}

	IndexedFinder algo(effectLength);
	for (auto p : particles) {
		algo.add(p);
	}
	algo.createPairs();
	const auto& pairs = algo.getPairs();

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = static_cast<CSPHParticle*>(pairs[i].first);
		auto p2 = static_cast<CSPHParticle*>(pairs[i].second);
		p1->addDensity(*p2);
		p2->addDensity(*p1);
	}

	for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
		particles[i]->addSelfDensity();
	}

#pragma omp parallel for
	for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
		auto p1 = static_cast<CSPHParticle*>(pairs[i].first);
		auto p2 = static_cast<CSPHParticle*>(pairs[i].second);
		p1->solvePressureForce(*p2);
		p2->solvePressureForce(*p1);
		p1->solveViscosityForce(*p2);
		p2->solveViscosityForce(*p1);
	}

	for (auto p : particles) {
		p->addExternalForce(externalForce);
	}

	CSPHBoundarySolver boundarySolver(timeStep, boundary);
	boundarySolver.solve(particles);

	for (auto p : particles) {
		p->forwardTime(timeStep);
	}
}