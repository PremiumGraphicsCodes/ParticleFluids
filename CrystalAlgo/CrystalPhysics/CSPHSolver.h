#pragma once

#include "SPHKernel.h"
#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Scene/IAnimator.h"
//#include "ISPHSolver.h"
#include <vector>

namespace Crystal {
	namespace Physics {
		class CSPHParticle;

class CSPHSolver : public Scene::IAnimator
{
public:
	CSPHSolver() : timeStep(0)
	{}

	void add(CSPHParticle* particle) {
		this->particles.push_back(particle);
	}

	void clear();

	void step() override;

	void simulate(const float timeStep);

	int getTimeStep() const { return timeStep; }

	std::vector<CSPHParticle*> getParticles() const { return particles; }

private:
	int timeStep;
	float effectLength = 1.25f;
	SPHKernel kernel;
	std::vector<CSPHParticle*> particles;
	Math::Vector3df externalForce;
};

	}
}