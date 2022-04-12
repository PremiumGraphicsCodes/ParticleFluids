#include "CrystalScene/Scene/IAnimator.h"
#include "CrystalPhysics/CrystalPhysicsCommand/PhysicsSolverExportCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

class SolverExporter : public IAnimator
{
public:
	explicit SolverExporter(World* model) :
		world(model)
	{}

	void add(Scene::IScene* f) { fluids.push_back(f); }

	void setDirectory(const std::filesystem::path& path) {
		this->path = path;
	}

	void step() override {
		PhysicsSolverExportCommand::Args args;
		std::vector<int> ids;
		for (auto f : fluids) {
			ids.push_back(f->getId());
		}
		args.fluidIds.setValue(ids);
		PhysicsSolverExportCommand command(args);
		command.execute(world);
	}

private:
	std::list<Scene::IScene*> fluids;
	std::filesystem::path path;
	World* world;
};
