#pragma once

#include <vector>

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"

#include "../../Crystal/Scene/IAnimator.h"

namespace Crystal {
	namespace Physics {

class PBSPHParticle;
class PBFluidScene;

class PBSPHSolver : public Scene::IAnimator
{
public:
	PBSPHSolver()
	{}

	void step() override;

	void add(PBFluidScene* fluid) { this->fluids.push_back(fluid); }

	void simulate(const float dt, const float effectRadius, const float searchRadius, const int maxIter);

	void setBoundary(const Math::Box3d& boundary) { this->boundary = boundary; }

	void setExternalForce(const Math::Vector3df& force) { this->externalForce = force; }

	//std::vector<PBSPHParticle*> getParticles() const { return particles; }

private:
	std::vector<PBFluidScene*> fluids;
	Math::Box3d boundary;
	Math::Vector3df externalForce;
};

	}
}