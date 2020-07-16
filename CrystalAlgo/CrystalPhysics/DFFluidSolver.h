#pragma once

#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"

#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {

class DFSPHParticle;
class DFFluidScene;

class DFFluidSolver : public Scene::IAnimator
{
public:
	DFFluidSolver();

	void step() override;

	void clear() { this->fluids.clear(); }

	void add(DFFluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const float dt, const float effectRadius, const float searchRadius, const int maxIter);

	void setBoundary(const Math::Box3d& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<PBSPHParticle*> getParticles() const { return particles; }

	void setTimeStep(const double dt) { this->maxTimeStep = dt; }

private:
	std::vector<DFFluidScene*> fluids;
	Math::Box3d boundary;
	Math::Vector3df externalForce;
	double maxTimeStep;

private:
	void correctDivergenceError();

	void correctDensityError();

	double calculateTimeStep(const std::vector<DFSPHParticle*>& particles);

};

	}
}