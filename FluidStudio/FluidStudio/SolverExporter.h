#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

namespace Crystal {
	namespace UI {

class SolverExporter : public IAnimator
{
public:
	explicit SolverExporter(World* model);

	//void clear() { this->fluids.clear(); }

	//void add(Scene::IScene* f) { fluids.push_back(f); }

	void setSolver(MVPFluidSolver* solver) { this->solver = solver; }

	void setDirectory(const std::filesystem::path& path) { this->path = path; }

	void step() override;

private:
	MVPFluidSolver* solver;
	//std::list<Scene::IScene*> fluids;
	std::filesystem::path path;
	World* world;
};

	}
}