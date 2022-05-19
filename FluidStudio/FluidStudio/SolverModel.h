#pragma once

#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidEmitterScene.h"
#include "CrystalPhysics/CrystalPhysics/MVP/MVPFluidSolver.h"
#include "FluidModel.h"
#include "EmitterModel.h"

#include "SolverExporter.h"
#include "IModel.h"

namespace PG {
	namespace FS {

class SolverModel : public IModel
{
public:
	void init(Crystal::Scene::World* world);

	void reset(Crystal::Scene::World* world);

	SolverExporter* getExporter() { return exporter; }

	Crystal::Physics::CSGBoundaryScene* getBoundary() { return csgScene; }

	Crystal::Physics::MVPFluidSolver* getSolver() { return &solver; }

	const std::vector<std::unique_ptr<PG::FS::FluidModel>>& getFluids() const { return fluids; }
	
	const std::vector<std::unique_ptr<PG::FS::EmitterModel>>& getEmitters() const { return emitters; }

	void addFluid(Crystal::Scene::World* world);

	void addEmitter(Crystal::Scene::World* world);

	tinyxml2::XMLElement* toXML(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent) override;

private:
	std::vector<std::unique_ptr<PG::FS::FluidModel>> fluids;
	std::vector<std::unique_ptr<PG::FS::EmitterModel>> emitters;
	SolverExporter* exporter;
	Crystal::Physics::MVPUpdater updator;
	Crystal::Physics::CSGBoundaryScene* csgScene;
	Crystal::Physics::MVPFluidSolver solver;
};

	}
}