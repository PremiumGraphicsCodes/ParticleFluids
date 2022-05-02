#include "MainModel.h"

using namespace Crystal::UI;

void MainModel::resetSolver()
{
	for (auto f : fluidScenes) {
		solver.addFluidScene(f);
		updator.add(f);
	}
	
	for (auto s : staticScenes) {
		solver.addBoundaryScene(s);
		updator.add(s);
	}
}
