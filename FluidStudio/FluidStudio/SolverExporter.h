#pragma once

#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"


namespace Crystal {
	namespace UI {

class SolverExporter : public Crystal::Scene::IAnimator
{
public:
	explicit SolverExporter(Crystal::Scene::World* model);

	//void clear() { this->fluids.clear(); }

	//void add(Scene::IScene* f) { fluids.push_back(f); }

	void setSolver(Crystal::Physics::MVPFluidSolver* solver) { this->solver = solver; }

	void setDirectory(const std::filesystem::path& path) { this->path = path; }

	void step() override;

	void setActive(const bool b) { this->isActive = b; }

	void setExportInterval(const int i) { this->interval = i; }

	void reset() { this->frame = 0; }

private:
	Crystal::Physics::MVPFluidSolver* solver;
	//std::list<Scene::IScene*> fluids;
	std::filesystem::path path;
	Crystal::Scene::World* world;
	bool isActive;
	int interval = 1;
	int frame;
};

	}
}