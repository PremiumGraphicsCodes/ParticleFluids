#pragma once

#include "SPHKernel.h"
#include "../../Crystal/Math/Box3d.h"
//#include "ISPHSolver.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class CSPHParticle;

class STSPHSolver
{
public:
	STSPHSolver() : timeStep(0)
	{}

	void add(CSPHParticle* particle) {
		this->particles.push_back(particle);
	}

	void clear();

	void simulate(const float effectLength, const float timeStep);

	int getTimeStep() const { return timeStep; }

	std::vector<CSPHParticle*> getParticles() const { return particles; }

private:
	int timeStep;
	SPHKernel kernel;
	std::vector<CSPHParticle*> particles;
	Math::Vector3df externalForce;
};

	}
}